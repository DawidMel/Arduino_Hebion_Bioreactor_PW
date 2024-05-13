#include<Arduino.h>
#include "my_encoder.hpp"

// not refactored

my_Rotary_encoder::my_Rotary_encoder(uint8_t pinA, uint8_t pinB, uint8_t pin_button, long sensitivity):
m_pinA(pinA),
m_pinB(pinB),
m_pin_button(pin_button),
m_sensitivity(sensitivity)
{
Serial.println("sensor was initialized");
}


void my_Rotary_encoder::init()
{
  pinMode (m_pinA, INPUT);
  pinMode (m_pinB, INPUT);
  pinMode(m_pin_button, INPUT_PULLUP);
  m_pinALast = digitalRead(m_pinA);
}


int my_Rotary_encoder::get_encoder_pos()
{
  return m_encoderPosCount;
}

void my_Rotary_encoder::emulate_phisical_move()
{
  m_encoderPosCount +=1;
  delay(1000);  //TODO REMOVE IT
}

void my_Rotary_encoder::check_encoder_pos()
{
 m_aVal = digitalRead(m_pinA);

  if ((m_aVal != m_pinALast) && (millis()>m_last_change+m_sensitivity)) 
  {     
    // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(m_pinB) != m_aVal) {  // Means pin A Changed first - We're Rotating Clockwise
      m_encoderPosCount ++;
    } else {
      m_encoderPosCount--;
    }
    Serial.print("Encoder Position: ");
    Serial.println(m_encoderPosCount);
    m_last_change=millis();
  }
  m_pinALast = m_aVal;

}


 int my_Rotary_encoder::get_encoder_move()
 {
   m_aVal = digitalRead(m_pinA);

  if ((m_aVal != m_pinALast) && (millis()>m_last_change+m_sensitivity)) 
  {     
    if (digitalRead(m_pinB) != m_aVal)  //3 value operator to make it simpler
    {
      m_last_change=millis();
      return 1;
    } 
    else 
    {
      m_last_change=millis();
      return -1;
    }
    
  }
  m_pinALast = m_aVal;
  return 0;
 }

float my_Rotary_encoder::set_value_(float initial_value, float step)
{
  m_encoderPosCount=0;
  float value_temp = initial_value;

  while(digitalRead(m_pin_button)==HIGH)
  {
    int encoder_return_val = this->get_encoder_move();
    value_temp += encoder_return_val*step;
    if(encoder_return_val != 0)
    {
      Serial.print("value: ");
      Serial.println(value_temp);
    }
  }
  return value_temp;
}

int my_Rotary_encoder::get_button_state()
{
  m_button_state = digitalRead(m_pin_button);
  return m_button_state;
}


  void my_Rotary_encoder::emulate_change_button_state()
  {
    m_button_state=(1-m_button_state);
  }