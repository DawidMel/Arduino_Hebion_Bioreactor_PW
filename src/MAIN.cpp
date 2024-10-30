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

EepromVariable ph_zero_shift(memory_manager);
EepromVariable ph_linear_factor(memory_manager);

EepromVariable oxg_zero_shift(memory_manager);
EepromVariable oxg_linear_factor(memory_manager);


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
MainController controller(DESIRE_PH, MAX_PH_ACCEPTABLE_DEVIATION, DESIRE_TEMP, MAX_TEMP_ACCEPTABLE_DEVIATION,3);
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

uint8_t is_sample_taking = 1;
uint8_t select_menu_option = 0;

#ifndef UNIT_TEST
void setup()
{
    // Serial port monitor initialization
    delay(500);
    Serial.begin(9600); 
    delay(500);

    //setting eeprom variable to default state SHOULD BE COMMENT!
    // thermometer.set_zero_shift(term_zero_shift,0.5);
    // thermometer.set_linear_factor(term_linear_factor,0.1);
    // ph_meter.set_zero_shift(ph_zero_shift,0.8);
    // ph_meter.set_linear_factor(ph_linear_factor,0.2);
    // oxygen_meter.set_zero_shift(oxg_zero_shift,2.1);
    // oxygen_meter.set_linear_factor(oxg_linear_factor,-0.1);

    // Initialize all physical components
    lcd.initialize(); //all error log will be write here so it must be initiated first
    delay(3000);
    encoder1.init();
    sd_men.init(lcd);
    delay(2000);
    sample_pump.init();
    acid_pump.init();
    alkaline_pump.init();
    thermometer.init();
    ph_meter.init();
    oxygen_meter.init();


    delay(100);
    //initial array with value of first measurement
     temperature_measurements_array.init(thermometer.get_rav_measure());
     ph_measurements_array.init(ph_meter.get_rav_measure());
     oxygen_measurements_array.init(oxygen_meter.get_rav_measure());

    delay(100);
    temperature =  meas_contr.calculate_temperature_from_meas_avg(temperature_measurements_array,thermometer);
    ph = meas_contr.calculate_ph_from_meas_avg(ph_measurements_array,ph_meter);
    oxygen_value = meas_contr.calculate_oxg_sat_from_meas_avg(oxygen_measurements_array,oxygen_meter, (uint8_t)temperature );

    delay(100);
    lcd.clear();

    
}

void loop()
{

    if(controller.return_menu_depth()==0) // default idle state
    {
        switch (abs(controller.get_menu_state())%2)
        {
        case 0:
            lcd.send_float_value(F("TEMP:"),temperature,0);
            lcd.send_string(F("data:"),my_data.return_data(),1);
            break;
        
        case 1:
            lcd.send_float_value(F("OXG:"),oxygen_value,0);
            lcd.send_float_value(F("PH:"),ph,1);
            break;
        
        default:
            break;
        }

    }

    if(controller.return_menu_depth()==1) // enter config menu
    {
            switch (abs(controller.get_menu_state()) % 7) //TODO change it to real value
            {
            case 0:
                lcd.send_float_value(F("ter_ZS:"), thermometer.get_zero_shift() ,0 );
                break;

            case 1:
                lcd.send_float_value(F("ter_lin:"), thermometer.get_linear_factor() , 0 );
                break;

            case 2:
                lcd.send_float_value(F("ph_ZS:"), ph_meter.get_zero_shift() , 0);
                break;

            case 3:
                lcd.send_float_value(F("ph_lin:"), ph_meter.get_linear_factor() , 0);
                break;

            case 4:
                lcd.send_float_value(F("oxg_ZS:"), oxygen_meter.get_zero_shift(),0 );
                break;

            case 5:
                lcd.send_float_value(F("oxg_lin:"), oxygen_meter.get_linear_factor(), 0);
                break;

            case 6:
                lcd.send_string(F("take sample:"), "", 0);
                break;

            default:
            {
                Serial.println(F("ERR"));
                break;
            }
            
    }
        select_menu_option = abs(controller.get_menu_state())%7;
    }


    if(controller.return_menu_depth()==2) //level of provoking action  
    {
        switch (select_menu_option%7)
        {
        case 0:
        controller.set_config_value(thermometer.get_zero_shift(),0.05,lcd,encoder1,"temp_zs");
            break;
        
        case 1:
        controller.set_config_value(thermometer.get_linear_factor(),0.01,lcd,encoder1,"temp_lf");
            break;
        
        case 2:
        controller.set_config_value(ph_meter.get_zero_shift(),0.05,lcd,encoder1,"ph_zs");
            break;

        case 3:
        controller.set_config_value(ph_meter.get_linear_factor(),0.01,lcd,encoder1,"ph_lf");
            break;

        case 4:
        controller.set_config_value(oxygen_meter.get_zero_shift(),0.05,lcd,encoder1,"oxg_zs");
            break;

        case 5:
        controller.set_config_value(oxygen_meter.get_linear_factor(),0.01,lcd,encoder1,"oxg_lf");
            break;
        
        case 6:
        lcd.send_string(F("do you want"), "", 0);
        lcd.send_string(F("take sample:"), "", 1);
        if(controller.get_menu_state()%2==0)
        {
            lcd.setCursor(13,1);
            lcd.print("n");
            is_sample_taking = 1;
        }
        else
        {
            lcd.setCursor(13,1);
            lcd.print("y");
            is_sample_taking = 0;
        }
            break;
        
        default:
        lcd.println(F("ERR"));
            break;
        }
    }







    if(controller.return_menu_depth()==3)
    {
        if((select_menu_option%7)<6)
        {
        lcd.send_string(F("change value"),"",0);
        lcd.send_float_value(F("val:"),controller.return_temp_val(),1);
        }

        switch (select_menu_option%7)
        {
        case 0:     
            thermometer.set_zero_shift(term_zero_shift, controller.return_temp_val());
            break;
        case 1:
            thermometer.set_linear_factor(term_linear_factor, controller.return_temp_val());
            break;
        
        case 2:
        ph_meter.set_zero_shift(ph_zero_shift, controller.return_temp_val());
            break;

        case 3:
        ph_meter.set_linear_factor(ph_linear_factor, controller.return_temp_val());
            break;

        case 4:
        oxygen_meter.set_zero_shift(oxg_zero_shift, controller.return_temp_val());
            break;
        
        case 5:
        oxygen_meter.set_linear_factor(oxg_linear_factor, controller.return_temp_val());
            break;

        case 6:

    
        if(is_sample_taking==0)
        {
        controller.start_taking_sample(sample_pump);
        is_sample_taking =1;
        lcd.clear();
        }
        else
        {   
            controller.skip_menu_depth();
            lcd.clear();
        }
            break;

        default:
        break;
        }

        controller.reset_menu_state();

    }









    //measurement run despite controller state
    if(meas_contr.get_measurement_state()==1)
    {
        temperature_measurements_array.add_measure(thermometer.get_rav_measure());
        ph_measurements_array.add_measure(ph_meter.get_rav_measure());
        oxygen_measurements_array.add_measure(oxygen_meter.get_rav_measure());
        amount_of_ready_measurement +=1;
    }

    if ((amount_of_ready_measurement%10)==9)
    {
        amount_of_ready_measurement = 0;

        //calculate real parameter
        temperature =  meas_contr.calculate_temperature_from_meas_avg(temperature_measurements_array,thermometer);
        ph = meas_contr.calculate_ph_from_meas_avg(ph_measurements_array,ph_meter);
        oxygen_value = meas_contr.calculate_oxg_sat_from_meas_avg(oxygen_measurements_array,oxygen_meter, (uint8_t)temperature );

        // SD writer run despite controller state
        sd_men.write_data_frame_to_sd(temperature,ph,oxygen_value,my_data);
    }

    meas_contr.check_is_measure_ready();
    controller.change_menu_depth(encoder1,lcd);
    controller.change_menu_state(encoder1,lcd);

    controller.calculate_correction_time(ph);   

    if(ph>DESIRE_PH+MAX_PH_ACCEPTABLE_DEVIATION)    //if ph to high
    controller.start_correction(acid_pump);         // pump some acid to mixture
    
    if(ph<DESIRE_PH-MAX_PH_ACCEPTABLE_DEVIATION)    //if ph to low
    controller.start_correction(alkaline_pump);     // pump some alkaline to mixture

    // pump stop function here to prevent not intentional execute
    controller.stop_taking_sample(sample_pump);
    controller.stop_correction(acid_pump);
    controller.stop_correction(alkaline_pump);
    
}
#endif