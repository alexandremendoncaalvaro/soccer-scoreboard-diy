#include "WifiPortal.h"

void WifiPortal::handleColors()
{
    auto json = server->arg(1);

    // https://arduinojson.org/v6/assistant/
    size_t capacity = 4 * JSON_OBJECT_SIZE(3) + 20;
    auto doc = fileSystem.jsonToDocument(json, capacity);

    Digits::ValueRGB colorT1 = {
        doc["t1"]["r"],
        doc["t1"]["g"],
        doc["t1"]["b"]};

    Digits::ValueRGB colorT2 = {
        doc["t2"]["r"],
        doc["t2"]["g"],
        doc["t2"]["b"]};

    Digits::ValueRGB colorTm = {
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
    auto doc = fileSystem.jsonToDocument(json, capacity);

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

void WifiPortal::setScoreTeamA()
{
    auto json = server->arg(1);
    size_t capacity = JSON_OBJECT_SIZE(1) + 40;
    auto doc = fileSystem.jsonToDocument(json, capacity);

    byte score = doc["score"];
    ledDisplay.set_ScoreTeamA(score);

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::setScoreTeamB()
{
    auto json = server->arg(1);
    size_t capacity = JSON_OBJECT_SIZE(1) + 40;
    auto doc = fileSystem.jsonToDocument(json, capacity);

    byte score = doc["score"];
    ledDisplay.set_ScoreTeamB(score);

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleClock()
{
    // DD/MM/YYYY hh:mm:ss
    // Message sample: { "datetime": "02/01/1985 00:20:00" }
    auto json = server->arg(1);

    // https://arduinojson.org/v6/assistant/
    size_t capacity = JSON_OBJECT_SIZE(1) + 40;
    auto doc = fileSystem.jsonToDocument(json, capacity);

    int year, month, day, hour, minute, second;
    const char *datetime = doc["datetime"];
    // Validação simples do formato: 10 caracteres para data, espaço, 8 para hora
    if (!datetime || strlen(datetime) != 19 || datetime[2] != '/' || datetime[5] != '/' || datetime[10] != ' ' || datetime[13] != ':' || datetime[16] != ':')
    {
        server->send(400, "text/json", "{\"result\":\"error\",\"message\":\"Formato esperado: DD/MM/YYYY hh:mm:ss\"}");
        return;
    }
    int parsed = sscanf(datetime, "%d/%d/%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second);
    if (parsed != 6 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59 || day < 1 || day > 31 || month < 1 || month > 12)
    {
        server->send(400, "text/json", "{\"result\":\"error\",\"message\":\"Valores inválidos para data/hora\"}");
        return;
    }
    if (!systemClock.setDateTime(year, month, day, hour, minute, second))
    {
        if (_debug)
            Serial.println(F("[WIFI PORTAL] Error setting date time"));
        server->send(500, "text/json", "{\"result\":\"error\"}");
        return;
    }
    if (_debug)
    {
        Serial.print(F("[POST CLOCK] JSON: "));
        Serial.println(json);
        systemClock.printTime();
    }

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleStartTimer()
{
    scoreboardClock.startResumeTimer();
    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handlePauseTimer()
{
    scoreboardClock.pauseTimer();
    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleStopTimer()
{
    scoreboardClock.stopTimer();
    ledDisplay.set_ScoreTeamA(0);
    ledDisplay.set_ScoreTeamB(0);
    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleSetDisplayMode()
{
    auto json = server->arg(1);
    size_t capacity = JSON_OBJECT_SIZE(1) + 20;
    auto doc = fileSystem.jsonToDocument(json, capacity);

    const char *mode = doc["mode"];
    if (!mode)
    {
        server->send(400, "text/json", "{\"result\":\"error\",\"message\":\"Campo mode ausente\"}");
        return;
    }

    scoreboardClock.setDisplayMode(strcmp(mode, "clock") == 0);
    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleNotFound()
{
    const char *metaRefreshStr = "<head><meta http-equiv=\"refresh\" content=\"0; url=http://192.168.1.1/index.html\" /></head><body><p>redirecting...</p></body>";
    server->send(200, "text/html", metaRefreshStr);
}

String WifiPortal::loadSettings()
{
    StaticJsonDocument<600> doc;
    doc["t1"]["r"] = ledDisplay.get_LedColor(1).r;
    doc["t1"]["g"] = ledDisplay.get_LedColor(1).g;
    doc["t1"]["b"] = ledDisplay.get_LedColor(1).b;
    doc["t2"]["r"] = ledDisplay.get_LedColor(2).r;
    doc["t2"]["g"] = ledDisplay.get_LedColor(2).g;
    doc["t2"]["b"] = ledDisplay.get_LedColor(2).b;
    doc["tm"]["r"] = ledDisplay.get_LedColor(3).r;
    doc["tm"]["g"] = ledDisplay.get_LedColor(3).g;
    doc["tm"]["b"] = ledDisplay.get_LedColor(3).b;
    doc["bright"] = ledDisplay.get_LedBrightness();
    String settings = "";
    serializeJson(doc, settings);
    return settings;
}

void WifiPortal::handleSaveSettings()
{
    String settings = loadSettings();
    fileSystem.saveSettings(settings);
    if (_debug)
    {
        Serial.println(F("[SETTINGS] Configuration Saved!"));
    }
    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleGetLedProperties()
{
    String settings = loadSettings();
    server->send(200, "text/json", settings);
}

bool WifiPortal::begin()
{
    if (_debug)
        Serial.println(F("[PORTAL] Starting Wifi Soft Access Point..."));
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.mode(WIFI_AP);
    IPAddress apIP(192, 168, 1, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

    auto isConnected = WiFi.softAP(_ssid, _password);
    // WiFi.setAutoReconnect(true);
    // WiFi.persistent(true);
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
    server->on(String(F("/getledprops")).c_str(), HTTP_GET, std::bind(&WifiPortal::handleGetLedProperties, this));
    server->on(String(F("/setcolors")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleColors, this));
    server->on(String(F("/setbrightness")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleBrightness, this));
    server->on(String(F("/setclock")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleClock, this));
    server->on(String(F("/save")).c_str(), HTTP_GET, std::bind(&WifiPortal::handleSaveSettings, this));
    server->on(String(F("/setscoreteama")).c_str(), HTTP_POST, std::bind(&WifiPortal::setScoreTeamA, this));
    server->on(String(F("/setscoreteamb")).c_str(), HTTP_POST, std::bind(&WifiPortal::setScoreTeamB, this));
    server->on(String(F("/starttimer")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleStartTimer, this));
    server->on(String(F("/pausetimer")).c_str(), HTTP_POST, std::bind(&WifiPortal::handlePauseTimer, this));
    server->on(String(F("/stoptimer")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleStopTimer, this));
    server->on(String(F("/setdisplaymode")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleSetDisplayMode, this));

    server->serveStatic("/", LittleFS, "/www/", "max-age=86400");
    server->serveStatic("/index.html", LittleFS, "/www/index.html", "max-age=86400");
    server->onNotFound(std::bind(&WifiPortal::handleNotFound, this));

    server->begin();

    if (_debug)
    {
        Serial.println(F("[PORTAL] HTTP server started!"));
        Serial.println();
    }
    return true;
}

void WifiPortal::handleClient()
{
    dnsServer->processNextRequest();
    server->handleClient();
}

WifiPortal wifiPortal;