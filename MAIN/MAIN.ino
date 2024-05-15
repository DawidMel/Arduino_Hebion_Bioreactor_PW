#include <AUnit.h>
#include <Arduino.h>
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
my_Rotary_encoder encoder1(REPINA, REPINB, REBUTTONPIN, SENSITIVITY);

SdMemoryManager sd_men(MOSIPIN, MISOPIN, SCKPIN, CSPIN); // last parameter is CS

PeristalticPump pump(9,13,13);
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
TimerLowPriority pump_timer;

/// flags
char pump_work_needed = 0;
char measurement = 0;
char display = 0;
char config = 1;

//TEMP FUNCTIONS

void test_led_setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(9, LOW);
}

void test_light_led(float read_ph, float dis_ph, float his)
{

  float current_ph = analogRead(A1);
  Serial.println(current_ph);

    if((read_ph-dis_ph)>his)
    {
        digitalWrite(6,HIGH);
    }

    else if ((dis_ph-read_ph)>his)
    {
        digitalWrite(7,HIGH);
    }

    else
    {
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
    }
    
}








void setup()
{

    Serial.begin(115200); // Serial port monitor initialization
    delay(2000);

    lcd.initialize();
    encoder1.init();
    sd_men.init();

    pump.init();

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
    pump_timer.reset();


    test_led_setup();
    delay(5000);
}

void loop()
{
    //////////////////////////////////////////////////////Unit tests////////////////////////////////////////////////////

    // aunit::TestRunner::run();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // think with need to be check as often as possible
    encoder1.check_encoder_pos();

    /// setting flags////
    measurement = measure_timer.activate(3000);
    display = display_timer.activate(10000);
    config = encoder1.get_button_state();
    pump_work_needed = pump_timer.activate(TIMEBETWENWORK);

    // if flag is set to 1 make action
    if (measurement == 1)
    {
        temperature_measurements_array.add_measure(thermometer.get_value_from_measurement());
        ph_measurements_array.add_measure(ph_meter.get_value_from_measurement());
        oxygen_measurements_array.add_measure(oxygen_meter.get_value_from_measurement());



        sd_men.write_data_frame_to_st(thermometer, ph_meter, oxygen_meter,my_data);
        sd_men.save();
        
        Serial.print(F("frame: "));
        Serial.println(sd_men.DEBUG_write_data_frame(thermometer, ph_meter, oxygen_meter, my_data));
        test_light_led(ph_meter.get_value(),7.0, 1.0);
    }

    if (display == 1)
    {
        lcd.clear();
        lcd.send_float_value(F("temp:"), temperature_measurements_array.get_average(), 0);
        lcd.send_float_value(F("ph:"), ph_measurements_array.get_average(), 1);
    }

    if (config == 0)
    {

        print_config_menu(encoder1, lcd, thermometer, ph_meter, oxygen_meter);
    }

    if(pump_work_needed && abs(ph_meter.get_value()-DESIRE_PH)>MAX_PH_ACCEPTABLE_DEVIATION)
    {
        Serial.println("HELLO ZDZIRO");
        pump.stabilize_ph(ph_meter.get_value(),DESIRE_PH);
    }

}

/*
most useful info:

start/stop serial monitor reset variable and who know dont reset arduino code

*/