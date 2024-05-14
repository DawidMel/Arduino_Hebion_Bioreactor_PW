#include "sd_memory.hpp"
#include "bioreactor_defined_const.hpp"
#include <SD.h>


SdMemoryManager::SdMemoryManager(uint8_t MOSI_pin, uint8_t MISO_pin, uint8_t SCK_pin, uint8_t CS)
    : m_MOSI_pin(MOSI_pin), m_MISO_pin(MISO_pin), m_SCK_pin(SCK_pin), m_CS(CS)
{
    m_filename = FILENAME;  //use defined filename
}

void SdMemoryManager::init()
{
    Serial.print(F("Init SD card "));

    if (!SD.begin(m_CS))
    {
        Serial.println(F("init failed"));
        while (true) 
            ;
    }
    m_filename = FILENAME;
    m_file = SD.open(FILENAME, FILE_WRITE);
    Serial.println(F("init done."));

    if (!m_file)
    {
        Serial.print(F("err open "));
        Serial.println(m_filename);
        while (true)
            ;
    }

    m_file.println();
    m_file.println("Hello World!");
    Serial.println(F("Star writing to file"));
}

void SdMemoryManager::write_to_st()
{
    m_file.println("TWOJA STARA");
}

 void SdMemoryManager::write_data_frame_to_st(Sensor& thermometer, Sensor& ph_meter, Sensor& oxygen_meter)
 {
    char buffer[20];
    sprintf(buffer, "%2f,%2f,%2f", thermometer, ph_meter,oxygen_meter); 
    // conversion is needed because arduino issues
    m_file.println(String(buffer));
 }

String SdMemoryManager::DEBUG_write_data_frame(Sensor& thermometer, Sensor& ph_meter, Sensor& oxygen_meter)
{
    char buffer[35];
    sprintf(buffer, "%.2f,%.2f,%.2f",  float(21.374208) /*float(thermometer.get_value())*/, float(ph_meter.get_value()), float(oxygen_meter.get_value())); 
    return(String(buffer));
}


void SdMemoryManager::close_file()
{
    m_file.close();
}