#include <Arduino.h>
#include "SystemClock.h"
#include "FileSystem.h"
#include "WifiPortal.h"
#include "IRRemote.h"

namespace BasicSettings
{
    bool _debug = false;
    void setLibsDebugOption(bool debug = false);
    void SerialBegin(unsigned long baudrate = 115200);
    void LoadSettings();

} // namespace BasicSettings