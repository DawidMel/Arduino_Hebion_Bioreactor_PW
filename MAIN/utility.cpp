#include <Arduino.h>
#include "utility.hpp"

measure_arr::measure_arr(int size):
array_size(size) 
{
  mesurment = new float[array_size]; // Dynamiczne utworzenie tablicy
  for (int i = 0; i < array_size; i++) {
    mesurment[i] = 0; // Zainicjowanie każdego elementu tablicy na 0
  }
}

void measure_arr::add_measure(float value)
{
  //oldest_mesure=mesurment[memory_cursor];  //TODO zakomentować jeśli nie używa się fasr
  mesurment[memory_cursor] = value;
  memory_cursor += 1;
  memory_cursor %= array_size;
}

float measure_arr::read_mesure(char index) {return mesurment[index];}


float measure_arr::get_average()  //TODO vectorization but not need now
{
  float sum =0;
  for(int i; i<=array_size; i++) {sum+=mesurment[i];}
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


/*
float measure_arr::get_average_fast() //LOOK OUT much faster but you need make sure if it is called at least before erray will be completly changed not recomended to use if not need
                                    // change value of average (old mesurment inside) if not called every mesurment UNTESTED!
{
  static int iteration = 0;
  static float inner_memory_cursorr = 0;
  float sum =0;

  if(iteration==0) {sum = get_average()*array_size;}
  else
  {
    if(inner_memory_cursorr!=memory_cursor)
    {
      sum-=oldest_mesure;
      sum+=mesurment[memory_cursor];
      inner_memory_cursorr==memory_cursor;
    }
  }

  iteration+=1;
  if(iteration>=100){iteration==0;}
}
*/