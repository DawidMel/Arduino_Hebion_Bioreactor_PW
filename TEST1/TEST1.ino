#include <EEPROM.h>
#include <Arduino.h>
#include <AUnit.h>

#include "eeprom_menager.hpp"
#include "sensor_config.hpp"
#include "utility.hpp"
#include "Unit_tests.hpp"




void setup() 
{

  Serial.begin(9600);  /*Inicjalizacja transmisji szeregowej z prędkością 9600 bitów na sekundę ~ 1200 znaków*/
  delay(2000);

  mesure_arr m1(20);


  Memory_menager menager1(0,500);
  Sensor termometr = setup_termometer_sensors(menager1);
  Sensor ph_meter = setup_ph_sensors(menager1);
  Sensor oxygen_meter = setup_oxygen_sensors(menager1);

  /////////////////////testy sensorow///////////////////////////
  //test_sensor(termometr,20,"termometr");
  //test_sensor(ph_meter,20,"ph_meter");
  //test_sensor(oxygen_meter,20,"oxygen_meter");

  
}

void loop() 
{
//testy jednostkowe

aunit::TestRunner::run();

/////////////////////

}