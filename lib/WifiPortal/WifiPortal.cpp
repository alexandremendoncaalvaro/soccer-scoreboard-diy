#include "WifiPortal.h"

bool WifiPortal::begin()
{
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.mode(WIFI_AP_STA);
    auto isConnected = WiFi.softAP(_ssid, _password); // IP is usually 192.168.4.1
    if (!isConnected)
    {
        if (_debug)
            Serial.print(F("[PORTAL] Soft AP connection error!"));
        return false;
    }

    if (_debug)
    {
        Serial.println();
        Serial.print(F("[PORTAL] IP: "));
        Serial.println(WiFi.softAPIP());
    }

    httpUpdateServer.setup(&server);

    // Handlers

    server.on("/color", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/setdate", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/brightness", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/countdown", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/temperature", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/scoreboard", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/hourformat", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    server.on("/clock", HTTP_POST, []() {
        wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    });

    // Before uploading the files with the "ESP8266 Sketch Data Upload" tool, zip the files with the command "gzip -r ./data/" (on Windows I do this with a Git Bash)
    // *.gz files are automatically unpacked and served from your ESP (so you don't need to create a handler for each file).
    server.serveStatic("/", LittleFS, "/", "max-age=86400");

    server.begin(_serverPort);

    auto isFsOk = LittleFS.begin();

    if(!isFsOk)
    {
        if (_debug)
            Serial.println(F("[PORTAL] FileSystem error!"));
        return false;
    }

    if (_debug)
        Serial.println(F("[PORTAL] LittleFS contents:"));

    Dir dir = LittleFS.openDir("/");
    while (dir.next())
    {
        String fileName = dir.fileName();
        size_t fileSize = dir.fileSize();

        if (_debug)
            Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
    }

    if (_debug)
        Serial.println();

    return true;
}

void WifiPortal::handleClient()
{
    server.handleClient();
}

WifiPortal wifiPortal;