#include <Arduino.h>

#include <WiFi.h>
#include <mdns.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define SSID    SSID
#define PASSWD  PASSWD

#define MDNS_NAME MDNS_NAME

AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    if(!MDNS.begin(MDNS_NAME)) {
        Serial.printf("Error starting mDNS.\n");
    }
        
    Serial.printf("Connecting to %s...", SSID);

    WiFi.begin(SSID, PASSWD);
    while(WiFi.status() != WL_CONNECTED) {
        Serial.printf(".");
        delay(1000);
    }

    Serial.printf("\n");
    Serial.printf("ESP32 IP address: http://%s/\n", WiFi.localIP().toString().c_str());
    Serial.printf("ESP32 IP mdns: http://%s.local/\n", MDNS_NAME);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Welcome to ESP32 server.");
    });

    server.begin();
}

void loop() {

}
