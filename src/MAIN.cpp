#include <Arduino.h>
#include <AUnit.h>
#include <EEPROM.h>
#include <string.h>

#include "eeprom_menager.hpp"
#include "lcd_display.hpp"
#include "my_encoder.hpp"
#include "sd_memory.hpp"
#include "sensor_config.hpp"
#include "utility.hpp"
#include "steering_funct.hpp"

// create component responsible for managing eeprom
MemoryManager memory_manager(0, 500);

// create handler to eeprom memory value
// you MUST stay with this order else you need to reconfigure calibration factor
EepromVariable term_zero_shift(memory_manager);
EepromVariable term_linear_factor(memory_manager);
EepromVariable oxg_zero_shift(memory_manager);
EepromVariable oxg_linear_factor(memory_manager);
EepromVariable ph_zero_shift(memory_manager);
EepromVariable ph_linear_factor(memory_manager);


//create the sensors
Thermometer thermometer(THERMOMETER_PIN,term_zero_shift,term_linear_factor);
PhMeter ph_meter(PH_METER_PIN,ph_zero_shift,ph_linear_factor);
OxygenMeter oxygen_meter(OXYGEN_METER_PIN,oxg_zero_shift,oxg_linear_factor);

//create input-output components
MyLCD lcd(0x27, 16, 2);
MyRotaryEncoder encoder1(RE_CLK_PIN, RE_DT_PIN, RE_BUTTON_PIN, SENSITIVITY);
SdMemoryManager sd_men(SD_MOSI_PIN, SD_MISO_PIN, SD_SCK_PIN, SD_CS_PIN);

// create pump components
PeristalticPump sample_pump(PP_PWM_PIN,PP_MOTOR_NEGATIVE_PIN,PP_MOTOR_POSITIVE_PIN);
SimplePeristalticPump acid_pump(ACID_PUMP_PIN);
SimplePeristalticPump alkaline_pump(ALKALINE_PUMP_PIN);

// create main steering (virtual) components 
MainController controller(DESIRE_PH, MAX_PH_ACCEPTABLE_DEVIATION, DESIRE_TEMP, MAX_TEMP_ACCEPTABLE_DEVIATION,1);
MeasuringController meas_contr;

//create arrays for measures
MeasureArray temperature_measurements_array(10);
MeasureArray ph_measurements_array(10);
MeasureArray oxygen_measurements_array(10);

// create else useful object
DataHMS my_data(12, 30, 30); //data in Hours, Minutes, Seconds order 

// global variable (ONLY FOR CODE SIMPLICITY!)
uint8_t amount_of_ready_measurement = 0;
float temperature = 0;
float ph = 0;
float oxygen_value = 0;

#ifndef UNIT_TEST
void setup()
{
    // Serial port monitor initialization
    delay(500);
    Serial.begin(9600); 
    delay(500);

    // Initialize all physical components
    lcd.initialize(); //all error log will be write here so it must be initiated first
    encoder1.init();
    sd_men.init(lcd);
    sample_pump.init();
    acid_pump.init();
    alkaline_pump.init();
    thermometer.init();
    ph_meter.init();
    oxygen_meter.init();


    //initial array with value of first measurement
     temperature_measurements_array.init(thermometer.get_value());
     ph_measurements_array.init(ph_meter.get_value());
     oxygen_measurements_array.init(oxygen_meter.get_value());

    delay(500);  //5 seconds is for time to read init screen of LCD
    lcd.clear();
}

void loop()
{

    if(controller.return_menu_depth()==0) // default idle state
    {
        lcd.send_float_value("TEMP:",temperature,0);
        lcd.send_float_value("PH:",ph,1);
    }

    if(controller.return_menu_depth()==1) // enter config menu
    {
        lcd.send_float_value("oxg:",oxygen_value,0);
        lcd.send_string("data:",my_data.return_data(),1);
    }



    //measurement run despite controller state
    if(meas_contr.get_measurement_state()==1)
    {
        temperature_measurements_array.add_measure(thermometer.get_rav_measure());
        ph_measurements_array.add_measure(ph_meter.get_rav_measure());
        oxygen_measurements_array.add_measure(oxygen_meter.get_rav_measure());
        amount_of_ready_measurement +=1;

        Serial.println(thermometer.get_rav_measure());
        Serial.println(ph_meter.get_rav_measure());
        Serial.println(oxygen_meter.get_rav_measure());
    }

    if ((amount_of_ready_measurement%10)==9)
    {
        amount_of_ready_measurement = 0;

        //calculate real parameter

        temperature =  meas_contr.calculate_temperature_from_meas_avg(temperature_measurements_array,thermometer);
        ph = meas_contr.calculate_ph_from_meas_avg(ph_measurements_array,ph_meter);
        oxygen_value = meas_contr.calculate_oxg_sat_from_meas_avg(oxygen_measurements_array,oxygen_meter, (uint8_t)temperature );
        Serial.println("/////////////////////////");
        Serial.println(temperature);
        Serial.println(ph);
        Serial.println(oxygen_value);
        Serial.println("/////////////////////////");

        // SD writer run despite controller state
        sd_men.write_data_frame_to_sd(temperature,ph,oxygen_value,my_data);
    }

    meas_contr.check_is_measure_ready();
    controller.change_menu_depth(encoder1);

    

}
#endif