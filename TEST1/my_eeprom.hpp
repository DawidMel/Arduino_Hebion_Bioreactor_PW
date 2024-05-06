#include <avr/eeprom.h>
//menaning non-volatile memory
#ifndef MY_EEPROM
#define MY_EEPROM

#include <EEPROM.h>
/*
class EEPROM_DataField {
  float value;

  public:
  const int addr;

  EEPROM_DataField(const int addr);

  void setValue(float new_value);
  float getValue() const { return value; }
};

class EepromLineaFunction {
  EEPROM_DataField linear;
  EEPROM_DataField constans;
  public:
  EepromLineaFunction(const EEPROM_DataField & linear, const EEPROM_DataField & constans): linear(linear), constans(constans) {}
  EepromLineaFunction(int linear_addr, int constans_addr): linear(linear_addr, 1.0), constans(constans_addr, 0.0) {}
  EEPROM_DataField getLinear() const { return linear; }
  EEPROM_DataField getConstans() const { return constans; }

  float operator()(float x) const { return linear.getValue() * x + constans.getValue(); }
  
};


struct sensor_config
{

};

*/

#endif