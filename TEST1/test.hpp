// dołączanie biblotek
#include <Vector.h>
#include <EEPROM.h>


// własna przestrzeń adresowa
#ifndef TEST
#define TEST

class Memory_menager
{
  private:
  const int memory_start;
  const int memory_size;
  int memory_pointer;


  public:
  Memory_menager(int arg_memory_start, int arg_memory_lenght);
  int give_memory(int require_memoty);
};



class Sensor_config   //rename sensor_parameter
{
  public:             //zmienić na private
  int memory_addr;
  float value = -21.37;


  public:
  Sensor_config(Memory_menager& mem_manager);
  int change_config_value(float value);
  int get_config_value(void);
  float get_value();
  int get_addr();

};



class Sensor
{
  public:
  
  float value = 10;

  Sensor_config zero_shift, linear;



  Sensor(Sensor_config& szs, Sensor_config& lin);
  float get_value();
};










#endif //TEST