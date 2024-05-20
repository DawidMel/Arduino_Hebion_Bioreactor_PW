#include "my_encoder.hpp"
#include "bioreactor_defined_const.hpp"
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

long my_Rotary_encoder::return_button_inactivate_state_time()
{
    return m_button_inactivate_state_time;
}

int my_Rotary_encoder::get_button_state()
{   
    m_button_state = BUTTONDEFAULTSTATE;
    if ((m_button_inactivate_state_time + BUTTONSTAYONSTATE) < millis())
    {
        m_button_state = digitalRead(m_pin_button);
        m_button_inactivate_state_time = millis();
        if(m_button_state == 0)
        {
            m_button_depth +=1;
        }
        Serial.print("m_button_depth: ");
        Serial.println(m_button_depth);
    }
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

float my_Rotary_encoder::set_value(float initial_value, float step, MyLCD lcd)
{
    m_encoderPosCount = 0;
    float temp_value = initial_value;
    lcd.clear();
    while (digitalRead(m_pin_button) == HIGH)
    {
        int encoder_return_val = this->get_encoder_move();
        temp_value += encoder_return_val * step;
        lcd.send_float_value("",temp_value,0);
    }
    return temp_value;
}

    void my_Rotary_encoder::reset_encoder_pos()
    {
        m_encoderPosCount =0;
    }

    int my_Rotary_encoder::get_button_depth()
    {
        return m_button_depth;
    }
    void my_Rotary_encoder::reset__button_depth()
    {
        m_button_depth = 0;
    }