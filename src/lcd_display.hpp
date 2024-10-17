#ifndef LCD_DISPLAY_BR
#define LCD_DISPLAY_BR

#include<LiquidCrystal_I2C.h>
// not refactored

class MyLCD : public LiquidCrystal_I2C
{

  public:
  MyLCD(uint8_t addr, uint8_t column_num, uint8_t row_num);
  void initialize(); //TODO: better name 
  void send_float_value(String text, float value, int lcd_row); //TODO: change to template
  void send_string(String text, String value, int lcd_row);
};

#endif // LCD_DISPLAY_BR