//TODO REFACTOR WHOLE CLASS in way which Define is not used in CPP file

#ifndef SM_MEMORY
#define SM_MEMORY

#include <SD.h>
#include "eeprom_menager.hpp"
#include "utility.hpp"

/**
 * @class SdMemoryManager
 * @brief Main purpose is write data to SD card
 * 
 * this class mostly use function in SD.h library 
 * main idea is to create file and write data to it
 * 
 */
class SdMemoryManager
{
  private:
    // pins
    const uint8_t m_mosi_pin;
    const uint8_t m_miso_pin;
    const uint8_t m_sck_pin;
    const uint8_t m_cs_pin;

    uint8_t m_write_number=0;

    File m_file;
    const char * m_filename;
    unsigned long m_last_write = 0;

  public:

    SdMemoryManager(uint8_t mosi_pin, uint8_t miso_pin, uint8_t sck_pin, uint8_t cs_pin);

    /**
     * @brief 
     * 
     */
    void init(MyLCD lcd);
    /**
     * @brief 
     * 
     */
    void write_to_st();
    /**
     * @brief 
     * 
     * @param thermometer 
     * @param ph_meter 
     * @param oxygen_meter 
     * @param data 
     */
    void write_data_frame_to_st(Sensor& thermometer, Sensor& ph_meter, Sensor& oxygen_meter, DataHMS& data);
    String DEBUG_write_data_frame(Sensor& thermometer, Sensor& ph_meter, Sensor& oxygen_meter, DataHMS& data);
    void save();
    void close_file();
};

#endif

