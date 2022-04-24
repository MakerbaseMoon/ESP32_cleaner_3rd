#include <Arduino.h>
#include <ESP32GithubOTA.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "SPIFFS.h"

#define SSID SSID
#define PASSWD PASSWD

AsyncWebServer server(80);
ESP32PublicGithubOTA ota();

void setup() {
    if (!SPIFFS.begin(true)) {
        Serial.printf("SPIFFS begin error.\n");
        while(1);
    }

      Serial.printf("Connecting to %s...", SSID);

    WiFi.begin(SSID, PASSWD);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.printf(".");
        delay(1000);
    }

    Serial.printf("\n");
    Serial.printf("ESP32 IP address: %s\n", WiFi.localIP().toString().c_str());
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/main.js", "text/javascript");
    });

    server.on("/ota", HTTP_POST, [](AsyncWebServerRequest *request) {
        size_t params = request->params();
        for(size_t i = 0; i < params; i++) {
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("[%d]%s: %s\n", i, p->name().c_str(), p->value().c_str());
            int error = ota.firmwareOTA(p->value().c_str());
            Serial.printf("Error code: %d\n", error);
            if(error == 0) {
                ESP.restart();
            }
        }
        request->send(200, "text/plain", "OK");
    });

    server.begin();
}

void loop() {

}