#include "components.hpp"
#include <EEPROM.h>

#ifndef TEST
#define TEST

class MemoryManager
{
  private:
    const int m_memory_start;
    const int m_memory_size;
    int m_memory_pointer;

  public:
    MemoryManager(int memory_start, int memory_length);
    int give_memory(int require_memory);
};

class ConfigurationVariable // rename sensor_parameter
{
  private:
    int m_memory_addr;
    float m_value = -21.37;

  public:
    ConfigurationVariable(MemoryManager &mem_manager);
    int get_addr() const;
    float return_config_value() const;
    int retrieve_config_values_from_eeprom();
    void change_config_value(float value);
    
};

class Sensor
{
  private:
    float m_value = 10;

  public: // bad practice TODO in free time try to change to private
    ConfigurationVariable m_zero_shift, m_linear_factor;
    MeasuringDevice *m_measuring_device;

  public:
    Sensor(MeasuringDevice *measuring_dev, ConfigurationVariable &zero_shift, ConfigurationVariable &linear_factor);
    float get_value();
};

#endif // TEST