#include "my_encoder.hpp"
#include "bioreactor_defined_const.hpp"
#include <Arduino.h>

// not refactored

my_rotary_encoder::my_rotary_encoder(uint8_t clk_pin, uint8_t dt_pin, uint8_t button_pin, long sensitivity)
    : m_clk_pin(clk_pin), m_dt_pin(dt_pin), m_button_pin(button_pin), m_sensitivity(sensitivity)
{
    Serial.println(F("RE was init"));
}

void my_rotary_encoder::init()
{
    pinMode(m_clk_pin, INPUT);
    pinMode(m_dt_pin, INPUT);
    pinMode(m_button_pin, INPUT_PULLUP);
    m_clk_val_last = digitalRead(m_clk_pin);
}

uint8_t my_rotary_encoder::get_encoder_pos()
{
    return m_encoderPosCount;
}

uint8_t my_rotary_encoder::get_button_state()
{   
    uint8_t button_state = BUTTON_DEFAULT_STATE;
    if ((m_button_inactivate_state_time + BUTTON_STAY_ON_STATE) < millis())
    {
        button_state = digitalRead(m_button_pin);
        m_button_inactivate_state_time = millis();
    }
    return button_state;
}

uint8_t my_rotary_encoder::get_encoder_move()
{
    m_clk_val = digitalRead(m_clk_pin);

    if ((m_clk_val != m_clk_val_last) && (millis() > m_last_change + m_sensitivity))
    {
        if (digitalRead(m_dt_pin) != m_clk_val) // 3 value operator to make it simpler
        {
            m_last_change = millis();
            Serial.println(F("up"));
            return 1;
        }
        else
        {
            m_last_change = millis();
            Serial.println(F("down"));
            return -1;
        }
    }
    m_clk_val_last = m_clk_val;
    return 0;
}

void my_rotary_encoder::check_encoder_pos()
{
    m_clk_val = digitalRead(m_clk_pin);

    if ((m_clk_val != m_clk_val_last) && (millis() > m_last_change + m_sensitivity))
    {
        // Means the knob is rotating
        // if the knob is rotating, we need to determine direction
        // We do that by reading pin B.
        if (digitalRead(m_dt_pin) != m_clk_val)
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
    m_clk_val_last = m_clk_val;
}

float my_rotary_encoder::set_value(float initial_value, float step, MyLCD lcd)
{
    m_encoderPosCount = 0;
    float temp_value = initial_value;
    lcd.clear();
    while (digitalRead(m_button_pin) == HIGH)
    {
        int encoder_return_val = this->get_encoder_move();
        temp_value += encoder_return_val * step;
        lcd.send_float_value("",temp_value,0);
    }
    return temp_value;
}

    void my_rotary_encoder::reset_encoder_pos()
    {
        m_encoderPosCount =0;
    }