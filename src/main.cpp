#include "header.h"

void loadSettings()
{
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

void setup()
{
  setLibsDebugOption();

  Serial.begin(115200);
  if (DEBUG)
  {
    Serial.println(F("[SYSTEM] Serial Ok!"));
    Serial.println();

    Serial.println(F("[SYSTEM] Checking system Real Time Clock..."));
    systemClock.printTime();
  }

  auto fileSystemStarted = fileSystem.begin();
  if (DEBUG)
  {
    if (!fileSystemStarted)
      Serial.println(F("[SYSTEM] File System Error!"));
  }

  auto wifiPortalStarted = wifiPortal.begin();
  if (DEBUG)
  {
    if (!wifiPortalStarted)
      Serial.println(F("[SYSTEM] Wifi Portal Error!"));
  }

  auto ledDisplayStarted = ledDisplay.begin();
  if (DEBUG)
  {
    if (!ledDisplayStarted)
      Serial.println(F("[SYSTEM] Led Display Error!"));
  }

  loadSettings();
}

void loop()
{
  wifiPortal.handleClient();
  ledDisplay.updateLeds();
}
