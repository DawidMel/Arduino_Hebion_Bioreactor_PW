#include "utility.hpp"
#include "bioreactor_defined_const.hpp"
#include "eeprom_menager.hpp"
#include "lcd_display.hpp"
#include <Arduino.h>
#include "components.hpp"

MeasureArray::MeasureArray(int size) : m_array_size(size) //check for static alternative
{
    measurement = new int[m_array_size]; // Dynamic create of array
}

void MeasureArray::init(int initial_value)
{
    for (int i = 0; i < m_array_size; i++)
    {
        measurement[i] = initial_value;
    }
}

void MeasureArray::add_measure(int value) //cyclic list
{
    measurement[m_memory_cursor] = value;
    m_memory_cursor += 1;
    m_memory_cursor %= m_array_size;
}

float MeasureArray::read_measure(char index)
{
    return measurement[index];
}

float MeasureArray::get_average()
{
    long sum = 0;
    for (int i = 0; i < m_array_size; i++)
    {
        sum += measurement[i];
    }
    return (float(sum) / m_array_size); //conversion to float prevent int round effect (precision 7 digits instead of 5)
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






void print_config_menu(MyRotaryEncoder &encoder, MyLCD &lcd, Thermometer &term, PhMeter &ph, OxygenMeter &oxg)
{
            switch (2 % 7) //TODO change it to real value
            {
            case 0:
                lcd.send_float_value(F("ter_ZS:"), term.get_zero_shift(), 0);
                break;

            case 1:
                lcd.send_float_value(F("ter_lin:"), term.get_linear_factor(), 0);
                break;

            case 2:
                lcd.send_float_value(F("ph_ZS:"), ph.get_zero_shift(), 0);
                break;

            case 3:
                lcd.send_float_value(F("ph_lin:"), ph.get_linear_factor(), 0);
                break;

            case 4:
                lcd.send_float_value(F("oxg_ZS:"), oxg.get_zero_shift(), 0);
                break;

            case 5:
                lcd.send_float_value(F("oxg_lin:"), oxg.get_linear_factor(), 0);
                break;

            case 6:
                lcd.send_string(F("take sample:"), "", 0);
                break;

            default:
            {
                Serial.println(F("ERR"));
                break;
            }
            }
}