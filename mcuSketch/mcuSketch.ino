#include <SoftwareSerial.h>
#include <MyEventually.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <Time.h>

EvtManager mgr;

#define RX D3
#define TX D4
SoftwareSerial sSerial(RX, TX);

const char* ssid     = "WiFi";
const char* password = "H@ll0_Luc@5";
#define WIFI_LED_PIN D0
#define NTP_LED_PIN D5

int8_t timeZone = 2;
int8_t minutesTimeZone = 0;

void setPinModes() {
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  pinMode(WIFI_LED_PIN, OUTPUT);
  pinMode(NTP_LED_PIN, OUTPUT);
}

void setSerial() {
  Serial.begin(19200);
  while (!Serial) {
    delay(50);
  }
  sSerial.begin(57600);
  sSerial.write("MCU_SERIAL_READY");
}

void setWiFi() {
  WiFi.mode (WIFI_STA);
  WiFi.begin(ssid, password);
}

void setup () {  
  delay(2000);
  static WiFiEventHandler e1, e2;

  setPinModes();
  setSerial();
  setWiFi();

  NTP.onNTPSyncEvent ([](NTPSyncEvent_t event) {
    processSyncEvent (event);
  });

  e1 = WiFi.onStationModeGotIP (onConnect);
  e2 = WiFi.onStationModeDisconnected (onDisconnected);
}

void onConnect (WiFiEventStationModeGotIP ipInfo) {
  if (WiFi.status () == WL_CONNECTED) {
    sSerial.write("WIFI_CONNECTED___");
    switchLED(WIFI_LED_PIN, "ON");
    NTP.begin ("pool.ntp.org", timeZone, false, minutesTimeZone);
    //NTP.setDayLight(false);
    //NTP.setInterval (63, 3200);
  }
}

void onDisconnected (WiFiEventStationModeDisconnected event_info) {
  sSerial.write("WIFI_DISCONNECTED"); //17
  switchLED(WIFI_LED_PIN, "OFF");
  NTP.stop();
  //add event when wifi connects again
}

void processSyncEvent (NTPSyncEvent_t ntpEvent) {
  if (ntpEvent) {
    waitForTimeSync();
    if (ntpEvent == noResponse)
      sSerial.write("TIME_SYNC_ERROR:_NOT_REACHABLE");
    else if (ntpEvent == invalidAddress)
      sSerial.write("TIME_SYNC_ERROR:_INVALID_ADDRESS");
  } else {
    sendTimeToUNO();
    checkTimeSync();
  }
}

void sendTimeToUNO(){
  char *eventName = "GOT_TIME_SYNC:___";
  String dateTimeString = NTP.getTimeDateString(NTP.getLastNTPSync());
  String dateTime = eventName+ dateTimeString;
  const char *dateTimeChar = dateTime.c_str();
  sSerial.write(dateTimeChar);
}

bool hasAddedListener = false;
bool hasAddedWait = false;
void waitForTimeSync() {
  if (!hasAddedWait) {
    hasAddedWait = true;
    hasAddedListener = false;
    switchLED(NTP_LED_PIN, "OFF");
    mgr.resetContext();
    mgr.addListener(new EvtTimeListener(5100, true, (EvtAction)checkTimeSync));
    mgr.addListener(new EvtTimeListener(1000, true, (EvtAction)blinkNTPLED));
    mgr.addListener(new EvtAlwaysFiresListener((EvtAction)checkSerial));
  }
}

bool checkTimeSync() {
  if (year() != 1970) {
    if (!hasAddedListener) {
      hasAddedListener = true;
      hasAddedWait = false;
      switchLED(NTP_LED_PIN, "ON");
      mgr.resetContext();
      mgr.addListener(new EvtTimeListener(1000, true, (EvtAction)printTime));
      mgr.addListener(new EvtAlwaysFiresListener((EvtAction)checkSerial));
      return true;
    }
  } else {
    NTP.getTimeDateString();
  }
  return false;
}

bool printTime() {
  Serial.println (NTP.getTimeDateString ());
  return false;
}

bool checkSerial() {
  while (Serial.available() > 0) {
    sSerial.write(Serial.read());
  }
  while (sSerial.available() > 0) {
    Serial.write(sSerial.read());
  }
  return false;
}

bool blinkNTPLED() {
  bool state = digitalRead(NTP_LED_PIN);
  state = !state;
  digitalWrite(NTP_LED_PIN, state);
  return false;
}

void switchLED(int pin, String action) {
  if (digitalRead(pin) == LOW && action == "ON") {
    digitalWrite(pin, HIGH);
  } else if (digitalRead(pin) == HIGH && action == "OFF") {
    digitalWrite(pin, LOW);
  }
}

USE_EVENTUALLY_LOOP(mgr)
