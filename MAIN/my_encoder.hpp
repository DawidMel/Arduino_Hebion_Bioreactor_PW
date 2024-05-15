#ifndef MY_ENCODER
#define MY_ENCODER

#include <Arduino.h>
#include "lcd_display.hpp"


class my_Rotary_encoder
{
  private:
    const uint8_t m_pinA;
    const uint8_t m_pinB;
    const uint8_t m_pin_button;

    long m_sensitivity;
    long m_button_inactivate_state_time; //TODO rename
    long m_last_change;

    uint8_t m_aVal = 0;
    uint8_t m_pinALast = 0;
    uint8_t m_button_state = 1;
    int m_encoderPosCount;

  public:
    my_Rotary_encoder(uint8_t pinA, uint8_t pinB, uint8_t button, long sensitivity);
    void init();
    int get_encoder_pos();
    int get_button_state();
    long return_button_inactivate_state_time();
    void check_encoder_pos();
    void reset_encoder_pos();
    int get_encoder_move();
    float set_value(float initial_value, float step, MyLCD lcd);
};

#endif