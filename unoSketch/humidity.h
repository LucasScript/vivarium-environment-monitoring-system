#include "Arduino.h"

#define HUMID_CHANNEL_PIN 3
#define FAN_CHANNEL_PIN 2
int minHumidity = 80;
int maxHumidity = 90;
bool checkHumid()
{
    if ((int)humidity > (int)humidityError)
    {
        if ((int)humidity < (int)minHumidity || overHeat == true)
        {
            channelSwitch(HUMID_CHANNEL_PIN, "ON");
            channelSwitch(FAN_CHANNEL_PIN, "ON");
        }
        if ((int)humidity >= (int)maxHumidity && overHeat == false)
        {
            channelSwitch(HUMID_CHANNEL_PIN, "OFF");
            channelSwitch(FAN_CHANNEL_PIN, "OFF");
        }
    }
    return false;
}

String foggerState = "OFF";
void foggerSwitch()
{
    if (foggerState == "OFF")
    {
        foggerState = "ON";
        channelSwitch(HUMID_CHANNEL_PIN, "ON");
        channelSwitch(FAN_CHANNEL_PIN, "ON");
    }
    else if (foggerState == "ON")
    {
        foggerState = "OFF";
        channelSwitch(HUMID_CHANNEL_PIN, "OFF");
        channelSwitch(FAN_CHANNEL_PIN, "OFF");
    }
    delay(150);
}