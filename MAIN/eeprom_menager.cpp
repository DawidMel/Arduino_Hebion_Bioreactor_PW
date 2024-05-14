#include "eeprom_menager.hpp"
#include <EEPROM.h>

// MemoryManager
MemoryManager::MemoryManager(int memory_start, int memory_size)
    : m_memory_start(memory_start), m_memory_size(memory_size), m_memory_pointer(memory_start)
{
}

int MemoryManager::give_memory(int require_memory)
{
    int memory_max = m_memory_start + m_memory_size;

    if (require_memory <= memory_max - m_memory_pointer)
    {
        int returned_memory_addr = m_memory_pointer;
        m_memory_pointer += require_memory;
        return returned_memory_addr;
    }
    return -1; // TODO make sure that this case terminate process!!!
}

// sensor config
ConfigurationVariable::ConfigurationVariable(MemoryManager &mem_man)
    : m_memory_addr(
          mem_man.give_memory(sizeof(float))) // float is 4 byte  TODO change code to support any data structure (very low priority)
{
}

int ConfigurationVariable::get_addr() const
{
    return m_memory_addr;
}

float ConfigurationVariable::return_config_value() const
{
    return m_value;
}

int ConfigurationVariable::retrieve_config_values_from_eeprom(void)
{
    EEPROM.get(m_memory_addr, m_value);
}

void ConfigurationVariable::change_config_value(float value)
{
    m_value = value;
    EEPROM.put(m_memory_addr, m_value);
}

// Sensor
Sensor::Sensor(MeasuringDevice *measuring_dev, ConfigurationVariable &zero_shift, ConfigurationVariable &linear_factor)
    : m_zero_shift(zero_shift), m_linear_factor(linear_factor), m_measuring_device(measuring_dev)
{
}

float Sensor::get_value_from_measurement()
{
    m_value = m_measuring_device->get_value();
    return m_value * m_linear_factor.return_config_value() + m_zero_shift.return_config_value();
}

float Sensor::get_value()
{
    return m_value;
}