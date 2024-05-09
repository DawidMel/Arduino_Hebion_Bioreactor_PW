#include <EEPROM.h>
#include <Arduino.h>
#include <AUnit.h>

#include "eeprom_menager.hpp"
#include "sensor_config.hpp"
#include "utility.hpp"
#include "lcd_display.hpp"
#include "my_encoder.hpp"
//#include "Unit_tests.hpp"   //only for tests


//global variable
MemoryManager mem_manager(0,500);
Sensor thermometer = setup_thermometer_sensors(mem_manager);
Sensor ph_meter = setup_ph_sensors(mem_manager);
Sensor oxygen_meter = setup_oxygen_sensors(mem_manager);


//arrays for measures
MeasureArray temp_arr(30), ph_arr(40), oxygen_arr(50); //TODO think about this variable name

////timers
TimerLowPriority measure_timer, display_timer;

///flags
char measurement = 0;
char display = 0;


void setup() 
{

  Serial.begin(115200);  //Serial port monitor initialization
  delay(2000);

 
  /////////////////////sensors tests///////////////////////////
  test_sensor(thermometer,5,"thermometer");
  test_sensor(ph_meter,5,"ph_meter");
  test_sensor(oxygen_meter,5,"oxygen_meter");


  //timers reset
  measure_timer.reset();
  display_timer.reset();

}

void loop() 
{
//////////////////////////////////////////////////////Unit tests////////////////////////////////////////////////////

//aunit::TestRunner::run();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///setting flags////
measurement =  measure_timer.activate(1000);
display = display_timer.activate(10000);

//if flag is set to 1 make action

if(measurement==1)
{
  temp_arr.add_measure(thermometer.get_value());
  ph_arr.add_measure(ph_meter.get_value());
  oxygen_arr.add_measure(oxygen_meter.get_value());
}


if (display==1)
{
  Serial.print("thermometer avr value: ");
  Serial.println(temp_arr.get_average());

  Serial.print("ph_meter avr value: ");
  Serial.println(ph_arr.get_average());

  Serial.print("oxygen_meter avr value: ");
  Serial.println(oxygen_arr.get_average());
}

}
/*

in TODO file (not in git repo)

*/