#include "lcd_display.hpp"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// not refactored

MyLCD::MyLCD(uint8_t addr, uint8_t column_num, uint8_t row_num):
LiquidCrystal_I2C(addr,column_num,row_num)
{
}


void MyLCD::initialize()   //TODO check is we can omit this
{
  this->init(); 
  this->backlight();
  this->setCursor(3,0);
  this->print(F("BIOREACTOR"));
  this->setCursor(2,1);
  this->print(F("KNB HERBION"));
}



void MyLCD::send_float_value(String text, float value, int lcd_row)
{
  int text_length = text.length();
  String s_value = String(value);
  int s_value_length = s_value.length();

  this->setCursor(0,lcd_row);
  this->print(text);
  this->setCursor(text_length+1,lcd_row);
  this->print(s_value);


  if((s_value_length+text_length+1)>16)
  {
    this->setCursor(0,lcd_row);
    this->print(F("ERROR: MsgToLong"));

    Serial.println(text);
    Serial.println(text_length);
    Serial.println(s_value);
    Serial.println(s_value_length);
  }

}



void MyLCD::send_string(String text, String value, int lcd_row)
{
  int v_l = value.length();
  int t_l = text.length();

  this->setCursor(0,lcd_row);
  this->print(text);
  this->setCursor(t_l+1,lcd_row);
  this->print(value);


  if((v_l+t_l+1)>16)
  {
    this->setCursor(0,lcd_row);
    this->print(F("ERROR: MsgToLong"));

    Serial.println(text);
    Serial.println(t_l);
    Serial.println(value);
    Serial.println(v_l);
  }


}