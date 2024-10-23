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

/*

#include <SD.h>

const int chipSelect = 10;

// file name to use for writing
const char filename[] = "datalog.txt";

// File object to represent file
File myFile;
// string to buffer output
String dataBuffer;
// last time data was written to card:
unsigned long lastMillis = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // reserve 1 kB for String used as a dataBuffer
  dataBuffer.reserve(1024);

  // set LED pin to output, used to blink when writing
  pinMode(LED_BUILTIN, OUTPUT);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");

  // If you want to start from an empty file,
  // uncomment the next line:
  //  SD.remove(filename);
  // try to open the file for writing

  myFile = SD.open(filename, FILE_WRITE);
  if (!myFile) {
    Serial.print("error opening ");
    Serial.println(filename);
    while (true);
  }

  // add some new lines to start
  myFile.println();
  myFile.println("Hello World!");
  Serial.println("Starting to write to file...");
}

void loop() {
  // check if it's been over 10 ms since the last line added
  unsigned long now = millis();
  if ((now - lastMillis) >= 10) {
    // add a new line to the dataBuffer
    dataBuffer += "Hello ";
    dataBuffer += now;
    dataBuffer += "\r\n";
    // print the buffer length. This will change depending on when
    // data is actually written to the SD card file:
    Serial.print("Unsaved data buffer length (in bytes): ");
    Serial.println(dataBuffer.length());
    // note the time that the last line was added to the string
    lastMillis = now;
  }

  // check if the SD card is available to write data without blocking
  // and if the dataBuffered data is enough for the full chunk size
  unsigned int chunkSize = myFile.availableForWrite();
  if (chunkSize && dataBuffer.length() >= chunkSize) {
    // write to file and blink LED
    digitalWrite(LED_BUILTIN, HIGH);
    myFile.write(dataBuffer.c_str(), chunkSize);
    digitalWrite(LED_BUILTIN, LOW);
    // remove written data from dataBuffer
    dataBuffer.remove(0, chunkSize);
  }
}

*/