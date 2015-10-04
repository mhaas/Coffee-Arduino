
#ifndef WEB_SERVER_H

#define WEB_SERVER_H

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#include "SettingsStorage.h"

class WebServer {

  public:
    WebServer(SettingsStorage* settings);
    //~WebServer();
    void begin();
    void update();

  private:
    const char* DESIRED_TEMPERATURE_KEY = "desired_temp";
    const int HTTPD_PORT = 80;
    SettingsStorage* settings;
    ESP8266WebServer httpd;
    void handleRoot();
    void handleNotFound();
    void handleSet();
    void handleGet();
};


#endif
