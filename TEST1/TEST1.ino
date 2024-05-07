#include <EEPROM.h>
#include <Arduino.h>
#include <AUnit.h>

#include "eeprom_menager.hpp"
#include "sensor_config.hpp"
#include "utility.hpp"
//#include "Unit_tests.hpp"   //tylko do testów


//zmeinne globalne
Memory_menager menager1(0,500);
Sensor termometr = setup_termometer_sensors(menager1);
Sensor ph_meter = setup_ph_sensors(menager1);
Sensor oxygen_meter = setup_oxygen_sensors(menager1);


//tablice na dane pomiarowe
mesure_arr temp_arr(10), ph_arr(40), oxygen_arr(50);

////timery
TimerLowPriority mesure_timer, display_timer;

///flagi
char mesurment = 0;
char display = 0;


void setup() 
{

  Serial.begin(115200);  /*Inicjalizacja transmisji szeregowej z prędkością 9600 bitów na sekundę ~ 1200 znaków*/
  delay(2000);

 
  /////////////////////testy sensorow///////////////////////////
  test_sensor(termometr,1,"termometr");
  test_sensor(ph_meter,1,"ph_meter");
  test_sensor(oxygen_meter,1,"oxygen_meter");

//resetowanie timerów
mesure_timer.reset();
display_timer.reset();

}

void loop() 
{
//////////////////////////////////////////////////////testy jednostkowe////////////////////////////////////////////////////

//aunit::TestRunner::run();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///ustawianie flag////
mesurment =  mesure_timer.activate(1000);
display = display_timer.activate(10000);

//wykonywanie zadań jeśli flaga jest podniesiona

if(mesurment==1)
{
  temp_arr.add_mesure(termometr.get_value());
  ph_arr.add_mesure(ph_meter.get_value());
  oxygen_arr.add_mesure(oxygen_meter.get_value());
}


if (display==1)
{
Serial.print("termometr avr value: ");
Serial.println(temp_arr.get_average());

Serial.print("ph_meter avr value: ");
Serial.println(ph_arr.get_average());

Serial.print("oxygen_meter avr value: ");
Serial.println(oxygen_arr.get_average());
}

}