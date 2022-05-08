#include "header.h"

void setup()
{
  BasicSettings::setLibsDebugOption(true);
  BasicSettings::SerialBegin();
  if(!fileSystem.begin()){ return; };
  if(!wifiPortal.begin()){ return; };
  if(!ledDisplay.begin()){ return; };
  BasicSettings::LoadSettings();
}

void loop()
{
  wifiPortal.handleClient();
  ledDisplay.updateLeds();
}

namespace BasicSettings
{
    void setLibsDebugOption(bool debug)
    {
        _debug = debug;
        systemClock.set_debug(_debug);
        fileSystem.set_debug(_debug);
        wifiPortal.set_debug(_debug);
        ledDisplay.set_debug(_debug);
    }

    void SerialBegin(unsigned long baudrate)
    {
        Serial.begin(baudrate);
        if (_debug)
        {
            Serial.println(F("[SYSTEM] Serial Ok!"));
            Serial.println();

            Serial.println(F("[SYSTEM] Checking system Real Time Clock..."));
            systemClock.begin();
        }
    }

    void LoadSettings()
    {
        using namespace Digits;
        auto settingsString = fileSystem.loadSettings();

        // https://arduinojson.org/v6/assistant/
        size_t capacity = 3 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 30;
        auto doc = fileSystem.jsonToDocument(settingsString, capacity);

        ValueRGB colorT1 = {
            doc["t1"]["r"],
            doc["t1"]["g"],
            doc["t1"]["b"]};

        ValueRGB colorT2 = {
            doc["t2"]["r"],
            doc["t2"]["g"],
            doc["t2"]["b"]};

        ValueRGB colorTm = {
            doc["tm"]["r"],
            doc["tm"]["g"],
            doc["tm"]["b"]};

        byte brightness = doc["bright"];

        ledDisplay.set_LedColor(colorT1, 1);
        ledDisplay.set_LedColor(colorT2, 2);
        ledDisplay.set_LedColor(colorTm, 3);
        ledDisplay.set_LedBrightness(brightness);

        ledDisplay.updateLeds();
    }
}