#include "Arduino.h"

#define BUTTONS_ANALOG_PIN 0

#define RIGHT 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define SELECT 4
#define NONE 5

bool checkButtons()
{
    switch (readLCDButtons())
    {
    case RIGHT:
    {
        if (!menuMode)
        {
            //light on
        }
        else
        {
            menu.right();
        }
        delay(50);
        break;
    }
    case LEFT:
    {
        if (!menuMode)
        {
            // back light toggle
        }
        else
        {
            menu.left();
        }
        delay(50);
        break;
    }
    case UP:
    {
        if (!menuMode)
        {
            // heat lamp on
        }
        else
        {
            menu.up();
        }
        delay(50);
        break;
    }
    case DOWN:
    {
        if (!menuMode)
        {
            // humidity on
        }
        else
        {
            menu.down();
        }
        delay(50);
        break;
    }
    case SELECT:
    {
        if (!menuMode)
        {
            menuMode = true;
        }
        else
        {
            menu.select();
        }
        delay(50);
        break;
    }
    case NONE:
    default:
    {
        break;
    }
    }
}

int readLCDButtons()
{
    int buttonBeingPressed = 0;
    buttonBeingPressed = analogRead(BUTTONS_ANALOG_PIN);
    if (buttonBeingPressed > 1000)
        return NONE;
    if (buttonBeingPressed < 50)
        return RIGHT;
    if (buttonBeingPressed < 250)
        return UP;
    if (buttonBeingPressed < 450)
        return DOWN;
    if (buttonBeingPressed < 650)
        return LEFT;
    if (buttonBeingPressed < 850)
        return SELECT;
    return NONE;
}
