#include "my_encoder.hpp"
#include "bioreactor_defined_const.hpp"
#include <Arduino.h>

// not refactored

MyRotaryEncoder::MyRotaryEncoder(uint8_t clk_pin, uint8_t dt_pin, uint8_t button_pin, long sensitivity)
    : m_clk_pin(clk_pin), m_dt_pin(dt_pin), m_button_pin(button_pin), m_sensitivity(sensitivity)
{
    Serial.println(F("RE was init"));
}

void MyRotaryEncoder::init()
{
    pinMode(m_clk_pin, INPUT);
    pinMode(m_dt_pin, INPUT);
    pinMode(m_button_pin, INPUT_PULLUP);
    m_clk_val_last = digitalRead(m_clk_pin);
}

uint8_t MyRotaryEncoder::get_button_state()
{   
    uint8_t button_state = HIGH;
 
    if ((m_button_inactivate_state_time + BUTTON_STAY_ON_STATE < millis()) && digitalRead(m_button_pin)==LOW)
    {
        button_state = digitalRead(m_button_pin);
        m_button_inactivate_state_time = millis();
    }
    return button_state;
}

uint8_t MyRotaryEncoder::get_encoder_move()
{
    m_clk_val = digitalRead(m_clk_pin);

    if ((m_clk_val != m_clk_val_last) && (millis() > m_last_change + m_sensitivity))
    {
        if (digitalRead(m_dt_pin) != m_clk_val) // 3 value operator to make it simpler
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
    m_clk_val_last = m_clk_val;
}

