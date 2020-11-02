#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <LittleFS.h>

class WifiPortal
{
private:
    bool _debug = true;
    const char* _ssid = "Placar";
    const char* _password = "1234567890";
    int _serverPort = 80;
    ESP8266HTTPUpdateServer httpUpdateServer;

public:
    bool begin();
    void handleClient();
    ESP8266WebServer server;
};

extern WifiPortal wifiPortal;