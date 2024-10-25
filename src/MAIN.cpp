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
// #include "Unit_tests.hpp"   //only for tests

MemoryManager memory_manager(0, 500);

// EepromVariable  //TODO may set it in included hpp library?
EepromVariable term_zero_shift(memory_manager);
EepromVariable term_linear_factor(memory_manager);
EepromVariable oxg_zero_shift(memory_manager);
EepromVariable oxg_linear_factor(memory_manager);
EepromVariable ph_zero_shift(memory_manager);
EepromVariable ph_linear_factor(memory_manager);


Thermometer thermometer(THERMOMETER_PIN,term_zero_shift,term_linear_factor);
PhMeter ph_meter(PH_METER_PIN,ph_zero_shift,ph_linear_factor);
OxygenMeter oxygen_meter(OXYGEN_METER_PIN,oxg_zero_shift,oxg_linear_factor);


// global variable
MainController controller(DESIRE_PH, MAX_PH_ACCEPTABLE_DEVIATION, DESIRE_TEMP, MAX_TEMP_ACCEPTABLE_DEVIATION,3);
MeasuringController meas_contr;
DataHMS my_data(12, 30, 30);

//creating object of components
MyLCD lcd(0x27, 16, 2);
my_rotary_encoder encoder1(RE_CLK_PIN, RE_DT_PIN, RE_BUTTON_PIN, SENSITIVITY);
SdMemoryManager sd_men(SD_MOSI_PIN, SD_MISO_PIN, SD_SCK_PIN, SD_CS_PIN); // last parameter is CS
PeristalticPump sample_pump(PP_PWM_PIN,PP_MOTOR_NEGATIVE_PIN,PP_MOTOR_POSITIVE_PIN);
SimplePeristalticPump acid_pump(ACID_PUMP_PIN);
SimplePeristalticPump alkaline_pump(ALKALINE_PUMP_PIN);



// Sensor thermometer = setup_thermometer_sensors(memory_manager);
// Sensor ph_meter = setup_ph_sensors(memory_manager);
// Sensor oxygen_meter = setup_oxygen_sensors(memory_manager);


// arrays for measures
MeasureArray temperature_measurements_array(10);
MeasureArray ph_measurements_array(10);
MeasureArray oxygen_measurements_array(10); // TODO think about this variable name

void setup()
{
    delay(2000);
    Serial.begin(9600); // Serial port monitor initialization
    delay(2000);


    lcd.initialize(); //all error log will be write here so it must be initiated first
    encoder1.init();
    sd_men.init(lcd);
    sample_pump.init();
    acid_pump.init();
    alkaline_pump.init();
    // thermometer.init();
    // ph_meter.init();
    // oxygen_meter.init();



    ///////////////////sensors tests///////////////////////////
    // test_sensor(thermometer, 1, "thermometer");
    // test_sensor(ph_meter, 1, "ph_meter");
    // test_sensor(oxygen_meter, 1, "oxygen_meter");

    //set config variable
    term_zero_shift.change_eeprom_config_value(1);
    term_linear_factor.change_eeprom_config_value(2);
    ph_zero_shift.change_eeprom_config_value(3);
    ph_linear_factor.change_eeprom_config_value(4);
    oxg_zero_shift.change_eeprom_config_value(5);
    oxg_linear_factor.change_eeprom_config_value(6);

    float a,b,c,d,e,f;

    a = term_zero_shift.retrieve_config_values_from_eeprom();
    b = term_linear_factor.retrieve_config_values_from_eeprom();
    c = ph_zero_shift.retrieve_config_values_from_eeprom();
    d = ph_linear_factor.retrieve_config_values_from_eeprom();
    e = oxg_zero_shift.retrieve_config_values_from_eeprom();
    f = oxg_linear_factor.retrieve_config_values_from_eeprom();

    Serial.println();
    Serial.println();
    Serial.println();

    delay(6000);
    Serial.println(a);
    Serial.println(b);
    Serial.println(c);
    Serial.println(d);
    Serial.println(e);
    Serial.println(f);


    //initial array value is from measurement
     temperature_measurements_array.init(thermometer.get_value());
     ph_measurements_array.init(ph_meter.get_value());
     oxygen_measurements_array.init(oxygen_meter.get_value());

    Serial.println(F("HELLO we are after setup"));

    delay(1000);
}

void loop()
{

    delay(1000);

    //making measurement to array
    temperature_measurements_array.add_measure(meas_contr.rav_measure(thermometer));
    ph_measurements_array.add_measure(meas_contr.rav_measure(ph_meter));
    oxygen_measurements_array.add_measure(meas_contr.rav_measure(oxygen_meter));
    
    Serial.println(meas_contr.calculate_avg_from_meas(temperature_measurements_array,thermometer));
}