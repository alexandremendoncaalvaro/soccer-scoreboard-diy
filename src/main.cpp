#include "header.h"

void setup()
{
  setLibsDebugOption();

  Serial.begin(115200);
  if(DEBUG)
  {
    Serial.println(F("[SYSTEM] Serial Ok!"));
    Serial.println();

    Serial.println(F("[SYSTEM] Checking system Real Time Clock..."));
    systemClock.printTime();
  }
  
  auto wifiPortalStarted = wifiPortal.begin();
  if(DEBUG)
  {
    if (!wifiPortalStarted)
      Serial.println(F("[SYSTEM] Wifi Portal Error!"));
  }
}

void loop()
{
  wifiPortal.handleClient();
}
