#include "Arduino.h"

void setPinModes()
{
    pinMode(RX, INPUT);
    pinMode(TEMP_DATA_PIN, INPUT);
    pinMode(TEMP_CLOCK_PIN, INPUT);
    pinMode(LCD_BACK_LIGHT_PIN, INPUT);

    pinMode(TX, OUTPUT);
    pinMode(TEMP_CHANNEL_PIN, OUTPUT);  //channel 1
    pinMode(LIGHT_CHANNEL_PIN, OUTPUT); //channel 2
    pinMode(HUMID_CHANNEL_PIN, OUTPUT); //channel 3
    pinMode(FAN_CHANNEL_PIN, OUTPUT);   //channel 4
}

void channelSwitch(int pin, String action)
{
    if (digitalRead(pin) == LOW && action == "ON")
    {
        digitalWrite(pin, HIGH);
    }
    else if (digitalRead(pin) == HIGH && action == "OFF")
    {
        digitalWrite(pin, LOW);
    }
}

bool backLightState = INPUT;
void backLightSwitch()
{
    backLightState = !backLightState;
    pinMode(LCD_BACK_LIGHT_PIN, backLightState);
    delay(150);
}