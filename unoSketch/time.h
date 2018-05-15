#include "Arduino.h"

#include <TimeLib.h>
#include <Time.h>

#define LIGHT_CHANNEL_PIN 11
int _year = 18;
int _month = 01;
int _day = 01;

int _hour = 00;
int _minute = 00;
int _second = 00;

int lightOnHour = 6;
int lightOnMin = 30;
int lightOffhour = 18;
int lightOffMin = 30;
bool vivLightOverride = false;

bool checkTime()
{
    if (!menuMode)
    {
        print(getTime(), 0, 0);
    }
    if (vivLightOverride == false)
    {
        if (hour() >= 6 && hour() <= 18)
        {
            if (hour() == 6 && minute() <= 30)
            {
                channelSwitch(LIGHT_CHANNEL_PIN, "OFF");
            }
            else if (hour() == 18 && minute() >= 30)
            {
                channelSwitch(LIGHT_CHANNEL_PIN, "OFF");
            }
            else
            {
                channelSwitch(LIGHT_CHANNEL_PIN, "ON");
            }
        }
        else
        {
            channelSwitch(LIGHT_CHANNEL_PIN, "OFF");
        }
    }
    return false;
}

void morningAlarm()
{
    channelSwitch(LIGHT_CHANNEL_PIN, "ON");
}

void eveningAlarm()
{
    channelSwitch(LIGHT_CHANNEL_PIN, "OFF");
}

void updateTime(int h, int mi, int s, int d, int m, int y)
{
    int _year = y;
    int _month = m;
    int _day = d;
    int _hour = h;
    int _minute = mi;
    int _second = s;
    setTime(_hour, _minute, _second, _day, _month, _year);
}

String getTime()
{
    return makeDoubleDigit(hour()) + ":" + makeDoubleDigit(minute()) + ":" + makeDoubleDigit(second());
}

String makeDoubleDigit(int d)
{
    if (d < 10)
        return "0" + String(d);
    return String(d);
}

String getDate()
{
    return makeDoubleDigit(day()) + "-" + makeDoubleDigit(month()) + "-" + makeDoubleDigit(year());
}

String vivLightState = "OFF";
void vivLightSwitch()
{
    if (vivLightState == "OFF")
    {
        vivLightState = "ON";
        channelSwitch(LIGHT_CHANNEL_PIN, "ON");
    }
    else if (vivLightState == "ON")
    {
        vivLightState = "OFF";
        channelSwitch(LIGHT_CHANNEL_PIN, "OFF");
    }
    delay(150);
}
