#include <Arduino.h>

#include <SPIFFS.h>

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

    if(!SPIFFS.begin()){ 
        Serial.printf("An Error has occurred while mounting SPIFFS\n");  
        while(1);
    }

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
        Serial.printf("Client to ESP32 server.\n");
        request.send(SPIFFS, "/index.html", "text/html");
    });

    server.begin();
}

void loop() {

}
