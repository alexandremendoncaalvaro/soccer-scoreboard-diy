#pragma once

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include "FileSystem.h"
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

    String loadSettings();

    void handleSaveSettings();
    void handleGetLedProperties();
    void handleColors();
    void handleBrightness();
    void handleClock();
    void handleNotFound();
    // void handleRoot();

public:
    void set_debug(bool debug) { _debug = debug; }
    bool begin();
    void handleClient();
};

extern WifiPortal wifiPortal;