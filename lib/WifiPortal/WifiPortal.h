#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "SystemClock.h"
#include "LedDisplay.h"

class WifiPortal
{
private:
    bool _debug = false;
    const char *_ssid = "Placar";
    const char *_password = "1234567890";
    const int _serverPort = 80;
    const byte _dnsPort = 53;

    std::unique_ptr<ESP8266WebServer> server;
    std::unique_ptr<DNSServer> dnsServer;
    
    // https://arduinojson.org/v6/assistant/
    DynamicJsonDocument jsonToDocument(String json, int numberOfElements, int messageLength);

    bool beginFileSystem();
    void handleColor();
    void handleBrightness();
    void handleClock();
    void handleNotFound();

public:
    void set_debug(bool debug);
    bool begin();
    void handleClient();
};

extern WifiPortal wifiPortal;