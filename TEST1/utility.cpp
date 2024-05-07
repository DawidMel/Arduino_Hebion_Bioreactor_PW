#include "utility.hpp"

mesure_arr::mesure_arr(int size):
array_size(size) 
{
  mesurment = new float[array_size]; // Dynamiczne utworzenie tablicy
  for (int i = 0; i < array_size; i++) {
    mesurment[i] = i; // Zainicjowanie każdego elementu tablicy na 0
  }
}

void mesure_arr::add_mesure(float value)
{
  mesurment[memory_cursor] = value;
  memory_cursor += 1;
  memory_cursor %= array_size;
}

float mesure_arr::read_mesure(char index)
{
  return mesurment[index];
}