#include "Arduino.h"

#include <SHT1x.h>
#define TEMP_DATA_PIN 15
#define TEMP_CLOCK_PIN 16
SHT1x sht1x(TEMP_DATA_PIN, TEMP_CLOCK_PIN);

int temperature = 0;
int humidity = 0;
int temperatureError = -39;
int humidityError = 0;
bool checkTemperature()
{
    float tempReading = round(sht1x.readTemperatureC());
    float humidReading = round(sht1x.readHumidity());
    temperature = int(tempReading);
    humidity = int(humidReading);
    if ((int)temperature < (int)temperatureError)
    {
        print(String("Temp read error"), 1, 0);
    }
    else if ((int)humidity < (int)humidityError)
    {
        print(String("Humid read error"), 1, 0);
    }
    else if (!menuMode)
    {
        print(String("T:" + String((int)temperature) + " H:" + String((int)humidity) + "   "), 1, 0);
    }
    return false;
}