#include <Arduino.h>
#include "SystemClock.h"
#include "FileSystem.h"
#include "WifiPortal.h"

const bool DEBUG = true;

void setLibsDebugOption()
{
  systemClock.set_debug(DEBUG);
  fileSystem.set_debug(DEBUG);
  wifiPortal.set_debug(DEBUG);
  ledDisplay.set_debug(DEBUG);
}