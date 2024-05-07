#include <EEPROM.h>
#include <Arduino.h>
#include <AUnit.h>

#include "eeprom_menager.hpp"
#include "sensor_config.hpp"
#include "utility.hpp"

//#include "Unit_tests.hpp" //uncoment before tests


Memory_menager menager1(0,500);
Sensor termometr = setup_termometer_sensors(menager1);
Sensor ph_meter = setup_ph_sensors(menager1);
Sensor oxygen_meter = setup_oxygen_sensors(menager1);



void setup() 
{

  Serial.begin(115200);  /*Inicjalizacja transmisji szeregowej z prędkością 9600 bitów na sekundę ~ 1200 znaków*/
  delay(2000);

 
  /////////////////////testy sensorow///////////////////////////
  //test_sensor(termometr,20,"termometr");
  //test_sensor(ph_meter,20,"ph_meter");
  //test_sensor(oxygen_meter,20,"oxygen_meter");

  
}

void loop() 
{
//testy jednostkowe

//aunit::TestRunner::run();

/////////////////////

delay(3000);
Serial.print("termometr value: ");
Serial.println(termometr.get_value());

Serial.print("ph_meter value: ");
Serial.println(ph_meter.get_value());

Serial.print("oxygen_meter value: ");
Serial.println(oxygen_meter.get_value());



}