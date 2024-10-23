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
// #include "Unit_tests.hpp"   //only for tests

// global variable

Config_var config_var(DESIRE_PH, MAX_PH_ACCEPTABLE_DEVIATION, DESIRE_TEMP, MAX_TEMP_ACCEPTABLE_DEVIATION);
DataHMS my_data(12, 30, 30);
MyLCD lcd(0x27, 16, 2);
my_rotary_encoder encoder1(RE_CLK_PIN, RE_DT_PIN, RE_BUTTON_PIN, SENSITIVITY);
SdMemoryManager sd_men(SD_MOSI_PIN, SD_MISO_PIN, SD_SCK_PIN, SD_CS_PIN); // last parameter is CS

PeristalticPump sample_pump(8,9,9);
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

////timers
TimerLowPriority measure_timer;
TimerLowPriority display_timer;
TimerLowPriority pump_activation_interval_timer;

TimerLowPriority pump1_timer;
TimerLowPriority pump2_timer;

/// flags
uint8_t pump_work_needed = 0;
uint8_t measurement = 0;
uint8_t display = 0;
uint8_t config = 1;

// flag masc - setting this value can inactivate flag even if it occur

// uint8_t masc_pump_work_needed = 1; unmasked flag
uint8_t masc_measurement = 1;
uint8_t masc_display = 1;
uint8_t masc_config = 1;


void setup()
{
    delay(2000);
    Serial.begin(9600); // Serial port monitor initialization
    delay(2000);

    lcd.initialize();
    encoder1.init();
    sd_men.init();

    sample_pump.init();
    acid_pump.init();
    alkaline_pump.init();

    thermometer.init();
    ph_meter.init();
    oxygen_meter.init();

    /////////////////////sensors tests///////////////////////////
    // test_sensor(thermometer, 1, "thermometer");
    // test_sensor(ph_meter, 1, "ph_meter");
    // test_sensor(oxygen_meter, 1, "oxygen_meter");

    // initial array value is from measurement
    temperature_measurements_array.init(thermometer.get_value_from_measurement());
    ph_measurements_array.init(ph_meter.get_value_from_measurement());
    oxygen_measurements_array.init(oxygen_meter.get_value_from_measurement());

    // timers reset
    measure_timer.reset();
    display_timer.reset();
    pump_activation_interval_timer.reset();

    delay(1000);
}

void loop()
{
encoder1.get_encoder_move();
Serial.println(encoder1.get_encoder_pos());
}