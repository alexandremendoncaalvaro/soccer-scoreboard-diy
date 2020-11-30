#pragma once

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

class FileSystem
{
private:
    bool _debug = false;

public:
    void set_debug(bool debug);

    bool saveSettings(String payload);
    String loadSettings();

    // https://arduinojson.org/v6/assistant/
    DynamicJsonDocument jsonToDocument(String json, size_t capacity);
    
    bool begin();
};

extern FileSystem fileSystem;