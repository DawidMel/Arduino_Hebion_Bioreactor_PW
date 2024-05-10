#include "eeprom_menager.hpp"
#include <EEPROM.h>

// MemoryManager
MemoryManager::MemoryManager(int arg_memory_start, int arg_memory_size)
    : memory_start(arg_memory_start), memory_size(arg_memory_size), memory_pointer(arg_memory_start)
{
}

int MemoryManager::give_memory(int arg_require_memory)
{
    int memory_max = memory_start + memory_size;

    if (arg_require_memory <= memory_max - memory_pointer)
    {
        int ret_val = memory_pointer;
        memory_pointer += arg_require_memory;
        return ret_val;
    }
    return -1;
}

// sensor config
ConfigurationVariable::ConfigurationVariable(MemoryManager &mem_man)
    : memory_addr(
          mem_man.give_memory(4)) // float is 4 byte  TODO change code to support any data structure (very low priority)
{
}

void ConfigurationVariable::change_config_value(float arg_value)
{
    value = arg_value;
    EEPROM.put(memory_addr, value);
}

int ConfigurationVariable::retrieve_config_values_from_eeprom(void)
{
    EEPROM.get(memory_addr, value);
}
float ConfigurationVariable::return_config_value()
{
    return value;
}
int ConfigurationVariable::get_addr()
{
    return memory_addr;
}

// Sensor
Sensor::Sensor(MeasuringDevice *measuring_dev, ConfigurationVariable &zero_shift, ConfigurationVariable &linear_factor)
    : zero_shift(zero_shift), linear_factor(linear_factor), measuring_device(measuring_dev)
{
}

float Sensor::get_value()
{
    value = measuring_device->get_value();
    return value * linear_factor.return_config_value() + zero_shift.return_config_value();
}
