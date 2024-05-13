#ifndef MY_ENCODER
#define MY_ENCODER

#include<Arduino.h>

class my_Rotary_encoder
{
  private:
    const uint8_t m_pinA;
    const uint8_t m_pinB;
    const uint8_t m_pin_button;

    long m_sensitivity;
    long m_last_change;

    int m_aVal = 0;
    int m_pinALast = 0;

    int m_button_state = 1;
    int m_encoderPosCount;

  public:
    my_Rotary_encoder(uint8_t pinA, uint8_t pinB, uint8_t button, long sensitivity);
    void init();
    int get_encoder_pos();



    void check_encoder_pos();

    float set_value_(float initial_value, float step);

    int get_button_state();


    int get_encoder_move();
};

#endif