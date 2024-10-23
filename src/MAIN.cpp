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

// global variable
MainController controller(DESIRE_PH, MAX_PH_ACCEPTABLE_DEVIATION, DESIRE_TEMP, MAX_TEMP_ACCEPTABLE_DEVIATION);
DataHMS my_data(12, 30, 30);

//creating object of components
MyLCD lcd(0x27, 16, 2);
my_rotary_encoder encoder1(RE_CLK_PIN, RE_DT_PIN, RE_BUTTON_PIN, SENSITIVITY);
SdMemoryManager sd_men(SD_MOSI_PIN, SD_MISO_PIN, SD_SCK_PIN, SD_CS_PIN); // last parameter is CS
PeristalticPump sample_pump(PP_PWM_PIN,PP_MOTOR_NEGATIVE_PIN,PP_MOTOR_POSITIVE_PIN);
SimplePeristalticPump acid_pump(ACID_PUMP_PIN);
SimplePeristalticPump alkaline_pump(ALKALINE_PUMP_PIN);


MemoryManager memory_manager(0, 500);
Sensor thermometer = setup_thermometer_sensors(memory_manager);
Sensor ph_meter = setup_ph_sensors(memory_manager);
Sensor oxygen_meter = setup_oxygen_sensors(memory_manager);


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
    thermometer.init();
    ph_meter.init();
    oxygen_meter.init();



    ///////////////////sensors tests///////////////////////////
    // test_sensor(thermometer, 1, "thermometer");
    // test_sensor(ph_meter, 1, "ph_meter");
    // test_sensor(oxygen_meter, 1, "oxygen_meter");

    //initial array value is from measurement
    temperature_measurements_array.init(thermometer.get_value_from_measurement());
    ph_measurements_array.init(ph_meter.get_value_from_measurement());
    oxygen_measurements_array.init(oxygen_meter.get_value_from_measurement());

    Serial.println(F("HELLO we are after setup"));

    delay(1000);
}

void loop()
{
    
}