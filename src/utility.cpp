#include "utility.hpp"
#include "bioreactor_defined_const.hpp"
#include "eeprom_menager.hpp"
#include "lcd_display.hpp"
#include <Arduino.h>

Config_var::Config_var(float desire_ph, float max_ph_acceptable_deviation, float desire_temp,
                       float max_temp_acceptable_deviation)
    : m_desire_ph(desire_ph), m_desire_temp(desire_temp), m_max_ph_acceptable_deviation(m_max_ph_acceptable_deviation),
      m_max_temp_acceptable_deviation(m_max_temp_acceptable_deviation)
{
}

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
        m_end_time = millis() + time_to_activate;
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
                       Sensor &term, Sensor &ph, Sensor &oxygen, PeristalticPump &pump)
{

    static long last_display_time = millis();
    static uint8_t chose_menu = 0;

    if(last_display_time + 1000 < millis() &&  chose_menu==0)
    {
    lcd.clear();
    lcd.send_string(F("CONFIG MENU"), " ", 0);
    last_display_time = millis();
    }

    int position_previous = encoder.get_encoder_pos();

    if (encoder.get_button_depth() == 1 )
    {

        encoder.check_encoder_pos();

        if (position_previous != encoder.get_encoder_pos())
        {
            chose_menu = 1;
            lcd.clear();

            switch (abs(encoder.get_encoder_pos()) % 5)
            {
            case 0:
                lcd.send_float_value(F("ter_ZS:"), term.m_zero_shift.return_config_value(), 0);
                break;

            case 1:
                lcd.send_float_value(F("ter_lin:"), term.m_linear_factor.return_config_value(), 0);
                break;

            case 2:
                lcd.send_float_value(F("ph_ZS:"), ph.m_zero_shift.return_config_value(), 0);
                break;

            case 3:
                lcd.send_float_value(F("ph_lin:"), ph.m_linear_factor.return_config_value(), 0);
                break;

            case 4:
                lcd.send_string(F("take sample:"), "", 0);
                break;

            default:
                Serial.println(F("ERR"));
                break;
            }

            position_previous = encoder.get_encoder_pos();
        }

    }
        if (encoder.get_button_depth() == 2)
        {
            int encoder_pos = encoder.get_encoder_pos(); // TODO improve it!
            float temp = 0;
            encoder.reset_encoder_pos();


            switch (abs(encoder_pos) % 5)
            {
            case 0:

                lcd.clear();
                lcd.send_float_value(F("TER ZS:"), term.m_zero_shift.return_config_value(), 0);
                delay(2000);

                temp = encoder.set_value(term.m_zero_shift.return_config_value(), 0.01, lcd);
                term.m_zero_shift.change_config_value(temp);
                break;

            case 1:

                lcd.clear();
                lcd.send_float_value(F("TER LIN:"), term.m_linear_factor.return_config_value(), 0);
                delay(2000);

                temp = encoder.set_value(term.m_linear_factor.return_config_value(), 0.01, lcd);
                term.m_linear_factor.change_config_value(temp);
                break;

            case 2:

                lcd.clear();
                lcd.send_float_value(F("PH ZS:"), ph.m_zero_shift.return_config_value(), 0);
                delay(2000);

                temp = encoder.set_value(ph.m_zero_shift.return_config_value(), 0.01, lcd);
                ph.m_zero_shift.change_config_value(temp);
                break;

            case 3:

                lcd.clear();
                lcd.send_float_value(F("PH LIN:"), ph.m_linear_factor.return_config_value(), 0);
                delay(2000);

                temp = encoder.set_value(ph.m_linear_factor.return_config_value(), 0.01, lcd);
                ph.m_linear_factor.change_config_value(temp);
                break;

            case 4:
                lcd.clear();
                lcd.send_string(F("TAKING SAMPLE:"), "", 0);
                delay(2000);
                pump.take_sample();
                encoder.reset__button_depth();
                break;

            default:
                Serial.println(F("ERR"));
                break;
            
        }        
    }

    if(encoder.get_button_depth()>2)
    {
        encoder.reset__button_depth();
        chose_menu = 0;     
    }

}