#ifndef MY_ENCODER
#define MY_ENCODER

#include <Arduino.h>
#include "lcd_display.hpp"


/**
 * @class MyRotaryEncoder
 * @brief 
 * 
 */
class MyRotaryEncoder
{
  private:
    const uint8_t m_clk_pin;
    const uint8_t m_dt_pin;
    const uint8_t m_button_pin;

    unsigned long m_sensitivity;
    unsigned long m_button_inactivate_state_time; //TODO rename
    unsigned long m_last_change;

    uint8_t m_clk_val = 0;
    uint8_t m_clk_val_last = 0;

  public:
    MyRotaryEncoder(uint8_t pin_a, uint8_t pin_b, uint8_t button, long sensitivity);
    void init();
    uint8_t get_button_state();
    uint8_t get_encoder_move();
};

#endif