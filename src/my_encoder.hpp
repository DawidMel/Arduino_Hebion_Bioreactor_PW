#ifndef MY_ENCODER
#define MY_ENCODER

#include <Arduino.h>
#include "lcd_display.hpp"


/**
 * @class my_rotary_encoder
 * @brief 
 * 
 */
class my_rotary_encoder
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
    uint8_t m_encoderPosCount;

  public:
    my_rotary_encoder(uint8_t pin_a, uint8_t pin_b, uint8_t button, long sensitivity);
    void init();
    uint8_t get_encoder_pos();
    uint8_t get_button_state();
    unsigned long return_button_inactivate_state_time();
    void check_encoder_pos();
    void reset_encoder_pos();
    uint8_t get_encoder_move();
    float set_value(float initial_value, float step, MyLCD lcd);
};

#endif