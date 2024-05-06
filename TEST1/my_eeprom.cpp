#include "EEPROM.h"
#include "my_eeprom.hpp"

#include <Arduino.h> // potrzebna do składni z arduino (np Serial.println() bez tego nie zadziała)
/*

EEPROM_DataField::EEPROM_DataField(const int addr, float value) :
addr(addr),
value(value)
{
  EEPROM.get(addr, value);
}

void EEPROM_DataField::setValue(float new_value)
{
  value = new_value;
  EEPROM.put(addr, value);
}


sensor_config::sensor_config(float termometr_const = 0.0, float termometer_linear=1.0,
                            float phmeter_const=0.0, float phmeter_linear=1.0,
                            float oxygen_sensor_const=0.0, float oxygen_sensor_linear=1.0)
: termometr_const(0, termometr_const)


{


}


*/
