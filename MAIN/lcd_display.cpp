#include "lcd_display.hpp"
#include <LiquidCrystal_I2C.h>

//not refactored

LiquidCrystal_I2C LCD_init(int I2C_addr, int col_num, int row_num)
{
    LiquidCrystal_I2C LCD(0x27, 20, 4);
    return LCD;
}
void print_message()
{
}