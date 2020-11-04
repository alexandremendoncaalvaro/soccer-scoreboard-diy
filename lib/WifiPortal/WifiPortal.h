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

    byte r_val = 255;
    byte g_val = 0;
    byte b_val = 0;

    ESP8266WebServer server;
    ESP8266HTTPUpdateServer httpUpdateServer;
    DNSServer dnsServer; 
    bool beginFileSystem();

public:
    bool begin();
    void handleClient();
};

extern WifiPortal wifiPortal;