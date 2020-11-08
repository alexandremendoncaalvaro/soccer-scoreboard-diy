#include "WifiPortal.h"

bool WifiPortal::beginFileSystem()
{
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

// void WifiPortal::handleGenericArgs()
// {
//     if (_debug)
//     {
//         Serial.println(server->args());

//         for (int i = 0; i < server->args(); i++)
//         {
//             Serial.print(server->argName(i)); //Get the name of the parameter
//             Serial.print(" - ");              //Get the name of the parameter
//             Serial.println(server->arg(i));   //Get the value of the parameter
//         }
//     }

//     server->send(200, "text/json", "{\"result\":\"ok\"}");
// }

void WifiPortal::handleConfig()
{
    // _valueR = server->arg(0).toInt();
    // _valueG = server->arg(1).toInt();
    // _valueB = server->arg(2).toInt();

    if (_debug)
    {
        // Serial.print(F("R: "));
        // Serial.println(_valueR);

        // Serial.print(F("G: "));
        // Serial.println(_valueG);

        // Serial.print(F("B: "));
        // Serial.println(_valueB);

        Serial.println(server->arg(1));
    }

    server->send(200, "text/json", "{\"result\":\"ok\"}");
}

void WifiPortal::handleNotFound()
{
    const char *metaRefreshStr = "<head><meta http-equiv=\"refresh\" content=\"0; url=http://192.168.1.1/index.html\" /></head><body><p>redirecting...</p></body>";
    server->send(200, "text/html", metaRefreshStr);
}

bool WifiPortal::begin()
{
    if (!beginFileSystem())
        return false;

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
        Serial.println();
        Serial.print(F("[PORTAL] IP: "));
        Serial.println(WiFi.softAPIP());
    }

    dnsServer.reset(new DNSServer());
    server.reset(new ESP8266WebServer(_serverPort));

    dnsServer->start(_dnsPort, "*", apIP);

    server->serveStatic("/", LittleFS, "/", "max-age=86400");
    server->on(String(F("/color")).c_str(), HTTP_POST, std::bind(&WifiPortal::handleConfig, this));
    server->onNotFound(std::bind(&WifiPortal::handleNotFound, this));

    server->begin();

    if (_debug)
    {
        Serial.println(F("[PORTAL] HTTP server started!"));
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