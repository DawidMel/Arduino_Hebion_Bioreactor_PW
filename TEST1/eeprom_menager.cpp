#include <EEPROM.h>
#include "eeprom_menager.hpp"



// Memory_menager
Memory_menager::Memory_menager(int arg_memory_start, int arg_memory_size):  //lista inicjalizacyjna
memory_start(arg_memory_start),
memory_size(arg_memory_size),
memory_pointer(arg_memory_start)
{}

int Memory_menager::give_memory(int arg_require_memoty)
{
  int memory_max = memory_start+memory_size;

  if(arg_require_memoty<=memory_max-memory_pointer)
  {
    int ret_val = memory_pointer;
    memory_pointer+=arg_require_memoty; 
    return ret_val;
  }
  return -1; 
}



// sensor config
Sensor_config::Sensor_config(Memory_menager & mem_man):
  memory_addr(mem_man.give_memory(4))  //float ma 4 bajty  TODO poprawić by mogło zaalokować dowolną wielkość i typ danych
{}

Sensor_config::change_config_value(float arg_value)
{
  value = arg_value;
  EEPROM.put(memory_addr, value);
}

int Sensor_config::get_config_value(void) {EEPROM.get(memory_addr, value);}
float Sensor_config::get_value() {return value;}
int Sensor_config::get_addr() {return memory_addr;}




//Sensor
Sensor::Sensor(Component& comp, Sensor_config& zero_shift,  Sensor_config& linear_factor):
zero_shift(zero_shift),
linear(linear_factor),
comp(comp)
{}

float Sensor::get_value()
{
  value = comp.get_value();
  return value*linear.get_value()+zero_shift.get_value();
}
void Sensor::collect_value(float arg_value) {value = arg_value;}


