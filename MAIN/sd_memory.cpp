#include<SD.h>
#include "sd_memory.hpp"
#include"bioreactor_defined_const.hpp"

SdMemoryManager::SdMemoryManager(uint8_t MOSI_pin, uint8_t MISO_pin, uint8_t SCK_pin, uint8_t CS):
m_MOSI_pin(MOSI_pin),
m_MISO_pin(MISO_pin),
m_SCK_pin(SCK_pin),
m_CS(CS)
{
m_filename = FILENAME;
}


void SdMemoryManager::init()
{
      Serial.print(F("Init SD card "));

  if (!SD.begin(m_CS))
  {
    Serial.println(F("init failed"));
    while (true);
  }

    //SD.remove(m_filename); //TODO should we reset file after reload?
    m_file = SD.open(m_filename, FILE_WRITE);
    Serial.println(F("init done."));

    if(!m_file)
    {
    Serial.print(F("err open "));
    Serial.println(m_filename);
    while (true);
    }


  m_file.println();
  m_file.println("Hello World!");
  Serial.println(F("Star writing to file"));

}

void SdMemoryManager::write_to_st()
{
  m_file.println("TWOJA STARA");
}

void SdMemoryManager::close_file()
{
  m_file.close();
}