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
EepromVariable::EepromVariable(MemoryManager &memory_manager)
    : m_memory_addr(
          memory_manager.give_memory(sizeof(float))) // float is 4 byte  TODO change code to support any data structure (very low priority)
{
}

int EepromVariable::get_addr() const
{
    return m_memory_addr;
}

float EepromVariable::retrieve_config_values_from_eeprom(void)
{
    float value_from_eeprom;
    EEPROM.get(m_memory_addr, value_from_eeprom);
    return value_from_eeprom;
}

void EepromVariable::change_eeprom_config_value(float value)
{

    EEPROM.put(m_memory_addr, value);
}
