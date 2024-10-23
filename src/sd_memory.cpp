#include "sd_memory.hpp"
#include "bioreactor_defined_const.hpp"
#include <SD.h>
#include "lcd_display.hpp"

SdMemoryManager::SdMemoryManager(uint8_t mosi_pin, uint8_t miso_pin, uint8_t sck_pin, uint8_t cs_pin)
    : m_mosi_pin(mosi_pin), m_miso_pin(miso_pin), m_sck_pin(sck_pin), m_cs_pin(cs_pin)
{
    m_filename = SD_FILENAME;  //use defined filename
}

void SdMemoryManager::init(MyLCD lcd)
{
    Serial.print(F("Init SD card "));

    if (!SD.begin(m_cs_pin))
    {
        Serial.println(F("init failed"));
        lcd.send_string(F("SD INIT FAIL!"),"",0);
        lcd.send_string(F("SD WON'T WORK"),"",1);
        delay(10000);
        exit(1);
    }
    m_filename = SD_FILENAME;
    m_file = SD.open(SD_FILENAME, FILE_WRITE);
    Serial.println(F("init done."));
    lcd.clear();
    lcd.send_string(F("SD init done"),"",0);
    delay(3000);

    if (!m_file)
    {
        Serial.print(F("err open "));
        Serial.println(m_filename);
        while (true)
            ;
    }

    m_file.println();
    m_file.println(F("temperature,ph,oxygen_concentration,data"));
    Serial.println(F("Star writing to file"));
}

void SdMemoryManager::write_to_st()
{
    m_file.println("w_test");
}

 void SdMemoryManager::write_data_frame_to_st(Sensor& thermometer, Sensor& ph_meter, Sensor& oxygen_meter, DataHMS& data)
 {
    String a = String(thermometer.get_value());
    String b = String(ph_meter.get_value());
    String c = String(oxygen_meter.get_value());

    String ans = a+","+b+","+c+","+data.return_data();
    m_file.println(ans);
 }

String SdMemoryManager::DEBUG_write_data_frame(Sensor& thermometer, Sensor& ph_meter, Sensor& oxygen_meter, DataHMS& data)
{
String a = String(thermometer.get_value());
String b = String(ph_meter.get_value());
String c = String(oxygen_meter.get_value());

return(a+","+b+","+c+","+data.return_data());
}


void SdMemoryManager::close_file()
{
    m_file.close();
}

void SdMemoryManager::save()
{
    if(m_write_number > 100)
    {
        m_file.close();
        m_file = SD.open(SD_FILENAME, FILE_WRITE);
        m_write_number = 0;
    }
    m_write_number+=1;
}