#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define SSID    SSID
#define PASSWD  PASSWD

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    Serial.printf("Connecting to %s...", SSID);

    WiFi.begin(SSID, PASSWD);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.printf(".");
        delay(1000);
    }

    Serial.printf("\n");
    Serial.printf("ESP32 IP address: %s\n", WiFi.localIP().toString().c_str());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Welcome to ESP32 server.");
    });

    server.begin();
}

void loop() {

}