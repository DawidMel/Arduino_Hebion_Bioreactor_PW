#include <Arduino.h>
#include "utility.hpp"

MeasureArray::MeasureArray(int size):
array_size(size) 
{
  measurement = new float[array_size]; // Dynamic create of array
  for (int i = 0; i < array_size; i++) {
    measurement[i] = 0; //Set every array element to zero TODO make measurement and use this value to initialize table!
  }
}

void MeasureArray::add_measure(float value)
{
  measurement[memory_cursor] = value;
  memory_cursor += 1;
  memory_cursor %= array_size;
}

float MeasureArray::read_measure(char index) {return measurement[index];}


float MeasureArray::get_average()  //TODO vectorization but not need now
{
  float sum =0;
  for(int i; i<=array_size; i++) {sum+=measurement[i];}
  return (sum/array_size);
}




TimerLowPriority::TimerLowPriority():
start_time(millis()),
end_time(millis())
{}

bool TimerLowPriority::activate(int time_to_activate)
{
    if (millis() >= end_time) {
        start_time = end_time;
        end_time = start_time + time_to_activate;
        return true;
    } else {
        return false;
    }
}

void TimerLowPriority::reset()
{
  start_time = millis();
  end_time = millis();
}


