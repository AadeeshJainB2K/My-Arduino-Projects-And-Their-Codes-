/*
    LCD_I2C - Arduino library to control a 16x2 LCD via an I2C adapter based on PCF8574

    Copyright(C) 2020 Blackhack <davidaristi.0504@gmail.com>

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according

/*
* When using lcd.print() (and almost everywhere you use string literals),
* is a good idea to use the macro F(String literal).
* This tells the compiler to store the string array in the flash memory
* instead of the ram memory. Usually you have more spare flash than ram.
* More info: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
*/
uint8_t happy[8] =
{
    0b00000,
    0b10001,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000,
    0b00000,
};

void setup()
{
    lcd.begin();
    lcd.backlight();
}

void loop()
{


    // Scroll left and right
    lcd.setCursor(0, 0);
   lcd.print(F(" "));
    lcd.print(F(" ATL Welcomes You"));
    lcd.print(F(" "));
     lcd.createChar(0, happy);
     lcd.write(0);
   
    {
        lcd.scrollDisplayLeft();
        delay(300);
    }
   

   
}
