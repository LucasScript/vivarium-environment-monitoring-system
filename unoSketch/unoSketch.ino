#include <MyEventually.h>

EvtManager mgr;

void setup()
{
  // setPinModes();
  // setSerial();
  // updateTime(_hour, _minute, _second, _day, _month, _year);

  // mgr.addListener(new EvtTimeListener(1150, true, (EvtAction)checkTime));
  // mgr.addListener(new EvtTimeListener(2500, true, (EvtAction)checkTemperature));
  // mgr.addListener(new EvtTimeListener(2550, true, (EvtAction)checkHeat));
  // mgr.addListener(new EvtTimeListener(2600, true, (EvtAction)checkHumid));
  // mgr.addListener(new EvtAlwaysFiresListener((EvtAction)checkSerial));
  // mgr.addListener(new EvtAlwaysFiresListener((EvtAction)checkButtons));
}

USE_EVENTUALLY_LOOP(mgr)