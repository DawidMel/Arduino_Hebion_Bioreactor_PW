#ifndef MY_UTILITY
#define MY_UTILITY

#include<string.h>
#include<Arduino.h>

#include "my_encoder.hpp"
#include "eeprom_menager.hpp"
#include "lcd_display.hpp"
#include "components.hpp"


class MeasureArray // TODO make inherence of this object to match sensor way of calculate
{
  private: //TODO: inheritance after arduino vector
  //TODO: is not good enough make it better
    const uint8_t m_array_size; // max 256 (but not recommended to use more than 100)
    int *measurement;      // Pointer array, will be initialized in constructor
    int m_memory_cursor = 0;
    float m_oldest_measure;

  public:
    MeasureArray(int size);
    void init(int initial_value); //TODO make it vector
    void add_measure(int value);
    float read_measure(char index);
    float get_average(); //TODO: add const

};

class TimerLowPriority
{
  private:
    unsigned long m_start_time;
    unsigned long m_end_time;

  public:
    TimerLowPriority();
    bool activate(int time_to_activate);
    void reset();
};

// TODO high priority timer

class DataHMS
{
  public:
    long m_offset;

  public:
    DataHMS(long hour, long minute, long second);
    String return_data(); //TODO const
};



void print_config_menu(MyRotaryEncoder &encoder, MyLCD &lcd, Thermometer &term, PhMeter &ph, OxygenMeter &oxg);

#endif