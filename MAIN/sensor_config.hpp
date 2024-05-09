#include "eeprom_menager.hpp"
#include <Arduino.h>
#include "components.hpp"
#include "bioreactor_defined_const.hpp"

#ifndef MY_SC
#define MY_SC

Sensor setup_thermometer_sensors(MemoryManager &manager);
Sensor setup_ph_sensors(MemoryManager &manager);
Sensor setup_oxygen_sensors(MemoryManager &manager);
void test_sensor(Sensor& sensor, float value_new, String sensor_name = "Sensor");


#endif