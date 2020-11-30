#include "FileSystem.h"

void FileSystem::set_debug(bool debug)
{
    _debug = debug;
}

bool FileSystem::begin()
{
    if (_debug)
        Serial.println(F("[FILESYSTEM] Starting FileSystem..."));

    auto isFileSystemOk = LittleFS.begin();

    if (!isFileSystemOk)
    {
        if (_debug)
            Serial.println(F("[FILESYSTEM] FileSystem error!"));
        return false;
    }

    if (_debug)
    {
        Serial.println(F("[FILESYSTEM] LittleFS contents:"));

        Dir dir = LittleFS.openDir("/");
        while (dir.next())
        {
            String fileName = dir.fileName();
            size_t fileSize = dir.fileSize();

            Serial.printf("[FILESYSTEM] Content: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
        }

        Serial.println();
    }

    return true;
}

DynamicJsonDocument FileSystem::jsonToDocument(String json, size_t capacity)
{
    DynamicJsonDocument doc(capacity);
    auto deserializationError = deserializeJson(doc, json);

    if (deserializationError)
    {
        if (_debug)
        {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(deserializationError.f_str());
        }
    }
    return doc;
}

bool FileSystem::saveSettings(String payload)
{
    File configFile = LittleFS.open("/settings.json", "w");
    configFile.print(payload);
}

String FileSystem::loadSettings()
{
    File configFile = LittleFS.open("/settings.json", "r");

    if (!configFile)
    {
        if (_debug)
            Serial.println(F("[FILESYSTEM] Failed to open config file"));
        return "";
    }

    size_t size = configFile.size();
    if (size > 1024)
    {
        if (_debug)
            Serial.println(F("[FILESYSTEM] Config file size is too large"));
        return "";
    }

    String result = configFile.readString();

    if (_debug)
    {
        Serial.println(F("[FILESYSTEM] Settings:"));
        Serial.println(result);
    }

    return result;
}

FileSystem fileSystem;