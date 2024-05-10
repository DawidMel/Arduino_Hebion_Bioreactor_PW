#include "utility.hpp"
#include <Arduino.h>

MeasureArray::MeasureArray(int size) : m_array_size(size)
{
    measurement = new float[m_array_size]; // Dynamic create of array
}

void MeasureArray::init(float initial_value)
{
    for (int i = 0; i < m_array_size; i++)
    {
        measurement[i] = initial_value;        
    }
}

void MeasureArray::add_measure(float value)
{
    measurement[m_memory_cursor] = value;
    m_memory_cursor += 1;
    m_memory_cursor %= m_array_size;
}

float MeasureArray::read_measure(char index)
{
    return measurement[index];
}

float MeasureArray::get_average() // TODO vectorization but not need now
{
    float sum = 0;
    for (int i = 0; i < m_array_size; i++)
    {
        sum += measurement[i];
    }
    return sum / m_array_size;
}

TimerLowPriority::TimerLowPriority() : m_start_time(millis()), m_end_time(millis())
{
}

bool TimerLowPriority::activate(int time_to_activate)
{
    if (millis() >= m_end_time)
    {
        m_start_time = m_end_time;
        m_end_time = m_start_time + time_to_activate;
        return true;
    }
    else
    {
        return false;
    }
}

void TimerLowPriority::reset()
{
    m_start_time = millis();
    m_end_time = millis();
}
