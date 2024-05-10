#include "components.hpp"
#include <EEPROM.h>

#ifndef TEST
#define TEST

class MemoryManager
{
  private:
    const int memory_start;
    const int memory_size;
    int memory_pointer;

  public:
    MemoryManager(int arg_memory_start, int arg_memory_length);
    int give_memory(int require_memory);
};

class ConfigurationVariable // rename sensor_parameter
{
  private:
    int memory_addr;
    float value = -21.37;

  public:
    ConfigurationVariable(MemoryManager &mem_manager);
    void change_config_value(float value);
    int retrieve_config_values_from_eeprom(void);
    float return_config_value();
    int get_addr();
};

class Sensor
{
  private:
    float value = 10;

  public: // bad practice TODO in free time try to change to private
    ConfigurationVariable zero_shift, linear_factor;
    MeasuringDevice *measuring_device;

  public:
    Sensor(MeasuringDevice *measuring_dev, ConfigurationVariable &zero_shift, ConfigurationVariable &linear_factor);
    float get_value();
};

#endif // TEST