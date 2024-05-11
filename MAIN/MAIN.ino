#include <AUnit.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>

#include "eeprom_menager.hpp"
#include "lcd_display.hpp"
#include "my_encoder.hpp"
#include "sensor_config.hpp"
#include "utility.hpp"
// #include "Unit_tests.hpp"   //only for tests

// global variable

DataHMS my_data(12,30,30);
MyLCD lcd(0x27, 16, 2);
my_Rotary_encoder encoder1(3, 4, 5, 150);


MemoryManager memory_manager(0, 500);
Sensor thermometer = setup_thermometer_sensors(memory_manager);
Sensor ph_meter = setup_ph_sensors(memory_manager);
Sensor oxygen_meter = setup_oxygen_sensors(memory_manager);

// arrays for measures
MeasureArray temperature_measurements_array(40), ph_measurements_array(40),
    oxygen_measurements_array(40); // TODO think about this variable name

////timers
TimerLowPriority measure_timer, display_timer;

/// flags
char measurement = 0;
char display = 0;
char config = 1;

void setup()
{

    Serial.begin(115200); // Serial port monitor initialization
    delay(2000);

    lcd.initialize();
    encoder1.init();

    /////////////////////sensors tests///////////////////////////
    // test_sensor(thermometer, 1, "thermometer");
    // test_sensor(ph_meter, 1, "ph_meter");
    // test_sensor(oxygen_meter, 1, "oxygen_meter");

    // initial array value is from measurement
    temperature_measurements_array.init(thermometer.get_value());
    ph_measurements_array.init(ph_meter.get_value());
    oxygen_measurements_array.init(oxygen_meter.get_value());

    // timers reset
    measure_timer.reset();
    display_timer.reset();


    // test z eeprom
    /*
    thermometer.m_linear_factor.change_config_value(encoder1.set_value_(1,0.01));
    Serial.println();
    Serial.println();
    Serial.print("thermometer linear_factor: ");
    Serial.println(thermometer.m_linear_factor.return_config_value());
    Serial.println();
    Serial.println();
    */
}

void loop()
{
    //////////////////////////////////////////////////////Unit tests////////////////////////////////////////////////////

    // aunit::TestRunner::run();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // think with need to be check as often as possible
    encoder1.check_encoder_pos();

    /// setting flags////
    measurement = measure_timer.activate(1000);
    display = display_timer.activate(10000);
    config = encoder1.get_button_state(); //0 when event occure


    // if flag is set to 1 make action
    if (measurement == 1)
    {
        temperature_measurements_array.add_measure(thermometer.get_value());
        ph_measurements_array.add_measure(ph_meter.get_value());
        oxygen_measurements_array.add_measure(oxygen_meter.get_value());
    }

    if (display == 1)
    {
        Serial.print(F("thermometer avr value: "));
        Serial.println(temperature_measurements_array.get_average());

        Serial.print(F("ph_meter avr value: "));
        Serial.println(ph_measurements_array.get_average());

        Serial.print(F("oxygen_meter avr value: "));
        Serial.println(oxygen_measurements_array.get_average());

        lcd.clear();
        lcd.send_float_value("temp:",temperature_measurements_array.get_average(),0);
        lcd.send_float_value("ph:",ph_measurements_array.get_average(),1);

        Serial.println("data: ");
        Serial.println(my_data.return_data());
    }

    if(config==0)
    {
        print_config_menu(encoder1);
    }

}

/*
most useful info:

start/stop serial monitor reset variable and who know dont reset arduino code

*/