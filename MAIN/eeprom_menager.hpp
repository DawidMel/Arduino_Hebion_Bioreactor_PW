// dołączanie biblotek
#include <EEPROM.h>
#include "components.hpp"

#ifndef TEST
#define TEST

class MemoryManager
{
  private:
  const int memory_start;
  const int memory_size;
  int memory_pointer;


  public:
  MemoryManager(int arg_memory_start, int arg_memory_lenght);
  int give_memory(int require_memory);
};



class Sensor_config   //rename sensor_parameter
{
  private:
  int memory_addr;
  float value = -21.37;


  public:
  Sensor_config(MemoryManager& mem_manager);
  int change_config_value(float value);
  int get_config_value(void);
  float get_value();
  int get_addr();

};



class Sensor
{
  private:
  float value = 10;

  public: //bad pratice in free time try to change to private
  Sensor_config zero_shift, linear;
  Component* comp;

  public:
  Sensor(Component* c, Sensor_config& zero_shift, Sensor_config& linear_factor);
  float get_value();
  void collect_value(float arg_value);
};










#endif //TEST