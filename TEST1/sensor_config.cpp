#include <string.h>
#include "eeprom_menager.hpp"
#include "sensor_config.hpp"


Sensor setup_termometer_sensors(Memory_menager &menager1)  //tutaj cała magia w ustawianiu sensorów 
{
  //termometr
  Sensor_config termometer_zero_shift(menager1);
  termometer_zero_shift.get_config_value();
  Sensor_config termometer_linear(menager1);
  termometer_linear.get_config_value();
  Sensor termometer(termometer_zero_shift, termometer_linear);
  return termometer;
}


Sensor setup_ph_sensors(Memory_menager &menager1)  //tutaj cała magia w ustawianiu sensorów 
{
 // ph-meter
  Sensor_config ph_zero_shift(menager1);
  ph_zero_shift.get_config_value();
  Sensor_config ph_linear(menager1);
  ph_linear.get_config_value();
  Sensor ph_meter(ph_zero_shift, ph_linear);
  return ph_meter;
}
  

Sensor setup_oxygen_sensors(Memory_menager &menager1)  //tutaj cała magia w ustawianiu sensorów 
{
  //sonda stezenia tlenu
  Sensor_config oxygen_zero_shift(menager1);
  oxygen_zero_shift.get_config_value();
  Sensor_config oxygen_linear(menager1);
  oxygen_linear.get_config_value();
  Sensor oxygen_meter(oxygen_zero_shift, oxygen_linear);
  return oxygen_meter;
}

void test_sensor(Sensor& sensor, float value_new, String sensor_name = "Sensor")  //TODO zmienić nazwę tej zmiennej
{
  delay(2000);

  Serial.print("wartosc przesuniecia_zera (po inicjalizacji) dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.zero_shift.get_value());


  sensor.zero_shift.get_config_value();


  Serial.print("wartosc przesuniecia_zera (po odczytaniu wartosci z eeprom) dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.zero_shift.get_value());

  Serial.print("adres w pamieci dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.zero_shift.get_addr());


  sensor.zero_shift.change_config_value(value_new);


  Serial.print("wartosc przesuniecia_zera (po zmianie na ustawiona wartosc) dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.zero_shift.get_value());
  Serial.println("----------------------------------------------------------------------------------------");



  Serial.print("wartosc wspolczynnika linowego (po inicjalizacji) dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.linear.get_value());


  sensor.linear.get_config_value();


  Serial.print("wartosc wspolczynnika linowego (po odczytaniu wartosci z eeprom) dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.linear.get_value());

  Serial.print("adres w pamieci dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.linear.get_addr());


  sensor.linear.change_config_value(value_new);


  Serial.print("wartosc wspolczynnika linowego (po zmianie na ustawiona wartosc) dla ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.linear.get_value());
  Serial.println("-----------------------------------------------------------------------------------------");



  Serial.print("wartosc odczytana (po uwzględnieniu wspolczynników) z czujnika ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.get_value());


  sensor.collect_value(value_new);
  Serial.print("wartosc odczytana (po wstawieniu nowej wartosci) z czujnika ");
  Serial.print(sensor_name);
  Serial.print(": ");
  Serial.println(sensor.get_value());


  Serial.println("-----------------------------------------------------------------------------------------");
  delay(2000);
}

