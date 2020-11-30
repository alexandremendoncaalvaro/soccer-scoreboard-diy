#include <Arduino.h>
#include "SystemClock.h"
#include "FileSystem.h"
#include "WifiPortal.h"

const bool DEBUG = true;

const long ledNumbers[] = {
    0b000111111111111111111, // [0] 0
    0b000111000000000000111, // [1] 1
    0b111111111000111111000, // [2] 2
    0b111111111000000111111, // [3] 3
    0b111111000111000000111, // [4] 4
    0b111000111111000111111, // [5] 5
    0b111000111111111111111, // [6] 6
    0b000111111000000000111, // [7] 7
    0b111111111111111111111, // [8] 8
    0b111111111111000111111, // [9] 9
    0b000000000000000000000, // [10] off
    0b111111111111000000000, // [11] degrees symbol
    0b000000111111111111000, // [12] C(elsius)
    0b111000111111111000000, // [13] F(ahrenheit)
};

void setLibsDebugOption()
{
  systemClock.set_debug(DEBUG);
  fileSystem.set_debug(DEBUG);
  wifiPortal.set_debug(DEBUG);
  ledDisplay.set_debug(DEBUG);
}