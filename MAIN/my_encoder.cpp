#include "my_encoder.hpp"
#include <Arduino.h>

// not refactored

my_Rotary_encoder::my_Rotary_encoder(uint8_t pinA, uint8_t pinB, uint8_t pin_button, long sensitivity)
    : m_pinA(pinA), m_pinB(pinB), m_pin_button(pin_button), m_sensitivity(sensitivity)
{
    Serial.println(F("RE was init"));
}

void my_Rotary_encoder::init()
{
    pinMode(m_pinA, INPUT);
    pinMode(m_pinB, INPUT);
    pinMode(m_pin_button, INPUT_PULLUP);
    m_pinALast = digitalRead(m_pinA);
}

int my_Rotary_encoder::get_encoder_pos()
{
    return m_encoderPosCount;
}

int my_Rotary_encoder::get_button_state()
{
    m_button_state = digitalRead(m_pin_button);
    return m_button_state;
}

int my_Rotary_encoder::get_encoder_move()
{
    m_aVal = digitalRead(m_pinA);

    if ((m_aVal != m_pinALast) && (millis() > m_last_change + m_sensitivity))
    {
        if (digitalRead(m_pinB) != m_aVal) // 3 value operator to make it simpler
        {
            m_last_change = millis();
            return 1;
        }
        else
        {
            m_last_change = millis();
            return -1;
        }
    }
    m_pinALast = m_aVal;
    return 0;
}

void my_Rotary_encoder::check_encoder_pos()
{
    m_aVal = digitalRead(m_pinA);

    if ((m_aVal != m_pinALast) && (millis() > m_last_change + m_sensitivity))
    {
        // Means the knob is rotating
        // if the knob is rotating, we need to determine direction
        // We do that by reading pin B.
        if (digitalRead(m_pinB) != m_aVal)
        {
            m_encoderPosCount++;
        }
        else
        {
            m_encoderPosCount--;
        }

        // Serial.print(F("RE pos: ")); debug only!
        Serial.println(m_encoderPosCount);
        m_last_change = millis();
    }
    m_pinALast = m_aVal;
}

float my_Rotary_encoder::set_value(float initial_value, float step)
{
    m_encoderPosCount = 0;
    float temp_value = initial_value;

    while (digitalRead(m_pin_button) == HIGH)
    {
        int encoder_return_val = this->get_encoder_move();
        temp_value += encoder_return_val * step;

        /*   DEBUG ONLY
                if (encoder_return_val != 0)
                {
                    Serial.print(F("value: "));
                    Serial.println(temp_value);
                }
        */
    }
    return temp_value;
}
