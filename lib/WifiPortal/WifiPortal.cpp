#include "WifiPortal.h"

void WifiPortal::set_debug(bool debug)
{
    _debug = debug;
}

bool WifiPortal::beginFileSystem()
{
    if (_debug)
        Serial.println(F("[PORTAL] Starting FileSystem..."));

    auto isFileSystemOk = LittleFS.begin();

    if (!isFileSystemOk)
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
            Serial.printf("[PORTAL] FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
    }

    if (_debug)
        Serial.println();

    return true;
}

DynamicJsonDocument WifiPortal::jsonToDocument(String json, size_t capacity)
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

void WifiPortal::handleColor()
{
    auto json = server->arg(1);

    // https://arduinojson.org/v6/assistant/
    size_t capacity = 4 * JSON_OBJECT_SIZE(3) + 20;
    auto doc = jsonToDocument(json, capacity);

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

    ledDisplay.set_LedColor(colorT1, 1);
    ledDisplay.set_LedColor(colorT2, 2);
    ledDisplay.set_LedColor(colorTm, 3);

    if (_debug)
    {
        Serial.print(F("[POST CONFIG] JSON: "));
        Serial.println(json);

        auto ledColor = ledDisplay.get_LedColor(1);
        Serial.print(F("[LED DISPLAY] T1 -> R: "));
        Serial.print(ledColor.r);
        Serial.print(F(", G: "));
        Serial.print(ledColor.g);
        Serial.print(F(", B: "));
        Serial.println(ledColor.b);
        ledColor = ledDisplay.get_LedColor(2);
        Serial.print(F("[LED DISPLAY] T2 -> R: "));
        Serial.print(ledColor.r);
        Serial.print(F(", G: "));
        Serial.print(ledColor.g);
        Serial.print(F(", B: "));
        Serial.println(ledColor.b);
        ledColor = ledDisplay.get_LedColor(3);
        Serial.print(F("[LED DISPLAY] TM -> R: "));
        Serial.print(ledColor.r);
        Serial.print(F(", G: "));
        Serial.print(ledColor.g);
        Serial.print(F(", B: "));
        Serial.println(ledColor.b);
        Serial.println();
    }

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleBrightness()
{
    auto json = server->arg(1);

    // https://arduinojson.org/v6/assistant/
    size_t capacity = JSON_OBJECT_SIZE(1) + 20;
    auto doc = jsonToDocument(json, capacity);

    byte brightness = doc["brightness"];

    ledDisplay.set_LedBrightness(brightness);

    if (_debug)
    {
        Serial.print(F("[POST CONFIG] JSON: "));
        Serial.println(json);

        auto ledBrightness = ledDisplay.get_LedBrightness();
        Serial.print(F("[LED DISPLAY] Brightness: "));
        Serial.print(ledBrightness);
        Serial.println();
    }

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleClock()
{
    // DD/MM/YYYY hh:mm:ss
    // Message sample: { "datetime": "02/01/1985 00:20:00" }
    auto json = server->arg(1);

    // https://arduinojson.org/v6/assistant/
    size_t capacity = JSON_OBJECT_SIZE(1) + 40;
    auto doc = jsonToDocument(json, capacity);

    int year, month, day, hour, minute, second;

    sscanf(doc["datetime"], "%d/%d/%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second);

    if (systemClock.setDateTime(year, month, day, hour, minute, second))
    {
        if (_debug)
        {
            Serial.print(F("[POST CLOCK] JSON: "));
            Serial.println(json);
            systemClock.printTime();
        }
    }

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleNotFound()
{
    const char *metaRefreshStr = "<head><meta http-equiv=\"refresh\" content=\"0; url=http://192.168.1.1/index.html\" /></head><body><p>redirecting...</p></body>";
    server->send(200, "text/html", metaRefreshStr);
}

void WifiPortal::handleGetLedProperties()
{
    StaticJsonDocument<200> doc;
    doc["tm"]["g"] = ledDisplay.get_LedColor(3).g;
    doc["tm"]["r"] = ledDisplay.get_LedColor(3).r;
    doc["tm"]["b"] = ledDisplay.get_LedColor(3).b;
    doc["bright"] = ledDisplay.get_LedBrightness();
    String payload = "";
    serializeJson(doc, payload);
    server->send(200, "text/json", payload);
}

bool WifiPortal::begin()
{
    if (!beginFileSystem())
        return false;

    if (_debug)
        Serial.println(F("[PORTAL] Starting Wifi Soft Access Point..."));
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.mode(WIFI_AP);
    IPAddress apIP(192, 168, 1, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    auto isConnected = WiFi.softAP(_ssid, _password);
    delay(500);

    if (!isConnected)
    {
        if (_debug)
            Serial.print(F("[PORTAL] Soft AP connection error!"));
        return false;
    }

    if (_debug)
    {
        Serial.println(F("[PORTAL] Wifi Connected!"));
        Serial.print(F("[PORTAL] IP: "));
        Serial.println(WiFi.softAPIP());

        Serial.println(F("[PORTAL] Starting HTTP Web Server..."));
    }

    dnsServer.reset(new DNSServer());
    server.reset(new ESP8266WebServer(_serverPort));

    dnsServer->start(_dnsPort, "*", apIP);

    // server->on(String(F("/")).c_str(), HTTP_GET, std::bind(&WifiPortal::handleRoot, this));
    server->on(String(F("/getled")).c_str(), HTTP_GET, std::bind(&WifiPortal::handleGetLedProperties, this));
    server->on(String(F("/setcolor")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleColor, this));
    server->on(String(F("/setbrightness")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleBrightness, this));
    server->on(String(F("/setclock")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleClock, this));

    server->serveStatic("/", LittleFS, "/", "max-age=86400");
    server->onNotFound(std::bind(&WifiPortal::handleNotFound, this));

    server->begin();

    if (_debug)
    {
        Serial.println(F("[PORTAL] HTTP server started!"));
        Serial.println();
    }
    return true;

    // server.on("/setdate", HTTP_POST, []() {
    //     // Sample input: date = "Dec 06 2009", time = "12:34:56"
    //     // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    //     String dateArg = wifiPortal.server.arg("date");
    //     String timeArg = wifiPortal.server.arg("time");
    //     char date[11];
    //     char time[9];

    //     int year, month, day, hour, minute, second;

    //     dateArg.toCharArray(date, 11);
    //     timeArg.toCharArray(time, 9);

    //     if (wifiPortal._debug)
    //     {
    //         Serial.print("Date: ");
    //         Serial.println(date);
    //         Serial.print("Time: ");
    //         Serial.println(time);
    //     }

    //     sscanf(date, "%d/%d/%d", &day, &month, &year);
    //     sscanf(time, "%d:%d:%d", &hour, &minute, &second);

    //     if (systemClock.setDateTime(year, month, day, hour, minute, second))
    //     {
    //         if (wifiPortal._debug)
    //         {
    //             systemClock.printTime();
    //         }
    //     }

    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // server.on("/brightness", HTTP_POST, []() {
    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // server.on("/countdown", HTTP_POST, []() {
    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // server.on("/temperature", HTTP_POST, []() {
    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // server.on("/scoreboard", HTTP_POST, []() {
    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // server.on("/hourformat", HTTP_POST, []() {
    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // server.on("/clock", HTTP_POST, []() {
    //     wifiPortal.server.send(200, "text/json", "{\"result\":\"ok\"}");
    // });

    // Before uploading the files with the "ESP8266 Sketch Data Upload" tool, zip the files with the command "gzip -r ./data/" (on Windows I do this with a Git Bash)
    // *.gz files are automatically unpacked and served from your ESP (so you don't need to create a handler for each file).
}

void WifiPortal::handleClient()
{
    dnsServer->processNextRequest();
    server->handleClient();
}

WifiPortal wifiPortal;