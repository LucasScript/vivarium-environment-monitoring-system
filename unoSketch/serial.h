#include "Arduino.h"
#include <SoftwareSerial.h>

#define RX 0
#define TX 1
SoftwareSerial sSerial(RX, TX);

void setSerial()
{
    Serial.begin(19200);
    while (!Serial)
    {
        delay(50);
    }
    Serial.println("Ready");
    sSerial.begin(57600);
}

#define arraySize 38
char inData[arraySize];
short index = 0;

bool checkSerial()
{
    while (Serial.available() > 0)
    {
        sSerial.write(Serial.read());
    }

    while (sSerial.available() > 0)
    {
        readData();
    }
    return false;
}

void readData()
{
    char inChar;
    if (sSerial.available() > 0)
    {
        index = 0;
        while (sSerial.available() > 0 && index < arraySize - 1)
        {
            inChar = sSerial.read();
            inData[index] = inChar;
            index++;
            inData[index] = '\0'; // Add a null at the end
        }
        processData();
    }
}

void processData()
{
    String actionString = String(inData).substring(0, 17);
    if (actionString == "TIME_SYNC_ERROR:_")
    {
        Serial.println("sync error");
    }
    else if (actionString == "WIFI_CONNECTED___")
    {
        Serial.println("wifi connected");
    }
    else if (actionString == "MCU_SERIAL_READY")
    {
        Serial.println("mcu ready");
    }
    else if (actionString == "GOT_TIME_SYNC:___")
    {
        String timeData = String(inData).substring(17, 36);
        int h = timeData.substring(0, 2).toInt();
        int mi = timeData.substring(3, 5).toInt();
        int s = timeData.substring(6, 8).toInt();
        int d = timeData.substring(9, 11).toInt();
        int m = timeData.substring(12, 14).toInt();
        int y = timeData.substring(15, 19).toInt();
        updateTime(h, mi, s, d, m, y);
        Serial.println(String(h) + "," + String(mi) + "," + String(s) + "," + String(d) + "," + String(m) + "," + String(y));
    }
    else
    {
        Serial.println("SYNC_ERROR");
    }
}
