#include <string.h>
#include "eeprom_menager.hpp"
#include "sensor_config.hpp"


Sensor setup_thermometer_sensors(MemoryManager &manager)  //setup the sensor 
{
  //thermometer
  Sensor_config thermometer_zero_shift(manager);
  thermometer_zero_shift.get_config_value();
  Sensor_config thermometer_linear(manager);
  thermometer_linear.get_config_value();
  ComponentThermometer* c_thermometer = new ComponentThermometer(TERMOMETHERPIN);
  Sensor thermometer(c_thermometer,thermometer_zero_shift, thermometer_linear);
  return thermometer;
}


Sensor setup_ph_sensors(MemoryManager &manager)  //setup the sensor  
{
  // ph-meter
  Sensor_config ph_zero_shift(manager);
  ph_zero_shift.get_config_value();
  Sensor_config ph_linear(manager);
  ph_linear.get_config_value();
  Component_ph_meter* c_ph_meter = new Component_ph_meter(PHMETERPIN);
  Sensor ph_meter(c_ph_meter, ph_zero_shift, ph_linear);
  return ph_meter;
}
  

Sensor setup_oxygen_sensors(MemoryManager &manager)  //setup the sensor 
{
   //oxygen meter 
  Sensor_config oxygen_zero_shift(manager);
  oxygen_zero_shift.get_config_value();
  Sensor_config oxygen_linear(manager);
  oxygen_linear.get_config_value();
  Component_oxygenmeter* c_oxygen_meter = new Component_oxygenmeter(OXYGENMETERPIN);
  Sensor oxygen_meter(c_oxygen_meter,oxygen_zero_shift, oxygen_linear);
  return oxygen_meter;
}





void test_sensor(Sensor& sensor, float value_new, String sensor_name = "Sensor")
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

