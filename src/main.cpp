#include <Arduino.h>

#include "SystemClock.h"
#include "WifiPortal.h"

void setup()
{
  Serial.begin(115200);
  wifiPortal.begin();
}

void loop()
{
  systemClock.getTime();
  wifiPortal.handleClient();
}
