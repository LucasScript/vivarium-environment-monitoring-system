#include "Arduino.h"

#define TEMP_CHANNEL_PIN 12

int minTemperature = 21;
int maxTemperature = 25;
int overHeatTemperature = 28;
bool overHeat = false;
bool checkHeat()
{
    if ((int)temperature > (int)temperatureError)
    {
        if ((int)temperature <= (int)minTemperature)
        {
            channelSwitch(TEMP_CHANNEL_PIN, "ON");
        }
        if ((int)temperature >= (int)maxTemperature)
        {
            channelSwitch(TEMP_CHANNEL_PIN, "OFF");
        }
        if ((int)temperature > (int)overHeatTemperature)
        {
            overHeat = true;
        }
        else
        {
            overHeat = false;
        }
    }
    return false;
}

String heatLampState = "OFF";
void heatLampSwitch()
{
    if (heatLampState == "OFF")
    {
        heatLampState = "ON";
        channelSwitch(TEMP_CHANNEL_PIN, "ON");
    }
    else if (heatLampState == "ON")
    {
        heatLampState = "OFF";
        channelSwitch(TEMP_CHANNEL_PIN, "OFF");
    }
    delay(150);
}