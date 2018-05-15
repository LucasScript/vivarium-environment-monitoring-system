#include "Arduino.h"
#include <LiquidCrystal.h>

#define LCD_PIN_4 4
#define LCD_PIN_5 5
#define LCD_PIN_6 6
#define LCD_PIN_7 7
#define LCD_PIN_RS 8
#define LCD_PIN_EN 9
#define LCD_BACK_LIGHT_PIN 10

LiquidCrystal lcd(LCD_PIN_RS, LCD_PIN_EN, LCD_PIN_4, LCD_PIN_5, LCD_PIN_6, LCD_PIN_7);

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
}

void print(String displayMessage, int line, int cursorPosition)
{
    lcd.setCursor(cursorPosition, line);
    lcd.print(displayMessage);
}