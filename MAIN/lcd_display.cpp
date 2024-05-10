#include "lcd_display.hpp"
#include <LiquidCrystal_I2C.h>

// it will be pull to main code directly

LiquidCrystal_I2C LCD_init(int I2C_addr, int col_num, int row_num)
{
    LiquidCrystal_I2C LCD(0x27, 20, 4);
    return LCD;
}
void Print_message()
{
}