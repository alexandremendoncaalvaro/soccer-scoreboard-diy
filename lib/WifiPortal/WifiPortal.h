#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#include "SystemClock.h" 

class WifiPortal
{
private:
    bool _debug = true;
    const char* _ssid = "Placar";
    const char* _password = "1234567890";
    const int _serverPort = 80;
    const byte _dnsPort = 53;

    byte _valueR = 255;
    byte _valueG = 0;
    byte _valueB = 0;

    std::unique_ptr<ESP8266WebServer> server;
    std::unique_ptr<DNSServer> dnsServer;
    // ESP8266HTTPUpdateServer httpUpdateServer;

    bool beginFileSystem();
    // void handleGenericArgs();
    void handleConfig();
    void handleNotFound();

public:
    bool begin();
    void handleClient();
};

extern WifiPortal wifiPortal;