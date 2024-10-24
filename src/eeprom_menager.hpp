#include "components.hpp"
#include <EEPROM.h>

#ifndef TEST
#define TEST

class MemoryManager
{
  private:
    const int m_memory_start;
    const int m_memory_size;
    int m_memory_pointer;    //declare in initializer as memory_start

  public:
    MemoryManager(int memory_start, int memory_length);
    int give_memory(int require_memory);
};

class EepromVariable 
{
  private:
    int m_memory_addr;

  public:
    EepromVariable(MemoryManager &mem_manager);
    int get_addr() const;
    float retrieve_config_values_from_eeprom();
    void change_eeprom_config_value(float value);
};

#endif // TEST