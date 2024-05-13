#include "utility.hpp"
#include "eeprom_menager.hpp"
#include "lcd_display.hpp"
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

DataHMS::DataHMS(long hour, long minute, long second) : m_offset(hour * 3600000 + minute * 60000 + second * 1000)
{
}

String DataHMS::return_data()
{
    long hour = ((m_offset + millis()) / 3600000) % 24;
    long minute = ((m_offset + millis()) / 60000) % 60;
    long secund = ((m_offset + millis()) / 1000) % 60;
    char buffer[9];

    sprintf(buffer, "%02d:%02d:%02d", (int)hour, (int)minute,
            (int)secund); // conversion is needed because arduino issues
    String my_data = String(buffer);
    return my_data;
}

// TODO rely bad practice IMPROVE IT ASAP
void print_config_menu(my_Rotary_encoder &encoder, MyLCD &lcd, // main sensors
                       Sensor &term, Sensor &ph, Sensor &oxygen)
{
    long temp_time = millis();
    int position_previous = encoder.get_encoder_pos();

    Serial.println(F("OPEN CONFIG MENU HURRY :)"));

    while (encoder.get_button_state() == 1 || temp_time + 3000 > millis())
    {
        encoder.check_encoder_pos();

        if (position_previous != encoder.get_encoder_pos())
        {
            lcd.clear();

            switch (abs(encoder.get_encoder_pos()) % 6)
            {
            case 0:
                lcd.send_float_value(F("term_ZS: "), term.m_zero_shift.return_config_value(), 0);
                break;

            case 1:
                lcd.send_float_value(F("term_lin: "), term.m_linear_factor.return_config_value(), 0);
                break;

            case 2:
                lcd.send_float_value(F("ph_ZS: "), ph.m_zero_shift.return_config_value(), 0);
                break;

            case 3:
                lcd.send_float_value(F("ph_lin: "), ph.m_linear_factor.return_config_value(), 0);
                break;

            case 4:
                lcd.send_float_value(F("oxygen_zs: "), oxygen.m_zero_shift.return_config_value(), 0);
                break;

            case 5:
                lcd.send_float_value(F("oxygen_lin: "), oxygen.m_linear_factor.return_config_value(), 0);
                break;

            default:
                Serial.println("OOOO");
                break;
            }

            position_previous = encoder.get_encoder_pos();
        }
    }
}