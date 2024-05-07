#include "eeprom_menager.hpp"
#include <Arduino.h>

#ifndef MY_SC
#define MY_SC

Sensor setup_termometer_sensors(Memory_menager &menager1);
Sensor setup_ph_sensors(Memory_menager &menager1);
Sensor setup_oxygen_sensors(Memory_menager &menager1);
void test_sensor(Sensor& sensor, float value_new, String sensor_name = "Sensor");


#endif