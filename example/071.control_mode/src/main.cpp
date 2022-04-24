#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "SPIFFS.h"

#define SSID SSID
#define PASSWD PASSWD

#define FAN_PIN 17

#define FAN_CHANNEL 1

#define FAN_FREQ 5000
#define FAN_RESOLUTION 8

#define MOTOR_A01 13
#define MOTOR_A02 15
#define MOTOR_B01 14
#define MOTOR_B02 12

#define MOTOR_CHANNEL_1 0x01
#define MOTOR_CHANNEL_2 0x02
#define MOTOR_CHANNEL_3 0x03
#define MOTOR_CHANNEL_4 0x04

#define MOTOR_FREQ 5000
#define MOTOR_RESOLUTION 8

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void forward();
void backward();
void left();
void right();
void stop();

void initWebSocket();
void handleWebSocketMessage(void*, uint8_t*, size_t, uint32_t);
void onEvent(AsyncWebSocket*, AsyncWebSocketClient*, AwsEventType, void*, uint8_t*, size_t);

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    ledcSetup(FAN_CHANNEL, FAN_FREQ, FAN_RESOLUTION);
    ledcAttachPin(FAN_PIN, FAN_CHANNEL);

    ledcSetup(MOTOR_CHANNEL_1, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_2, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_3, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_4, MOTOR_FREQ, MOTOR_RESOLUTION);

    ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_1);
    ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_2);
    ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_3);
    ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_4);

    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 0); 
    ledcWrite(FAN_CHANNEL, 0);

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

    server.on("/fan", HTTP_POST, [](AsyncWebServerRequest *request) {
        size_t params = request->params();
        for(size_t i = 0; i < params; i++) {
            AsyncWebParameter *p = request->getParam(i);
            Serial.printf("[%d]%s: %s\n", i, p->name().c_str(), p->value().c_str());
            ledcWrite(FAN_CHANNEL, p->value().toInt());
        }

        request->send(200, "text/plain", "OK");
    });

    initWebSocket();
    server.begin();
}

void loop() {
    ws.cleanupClients();
}

void forward() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 255);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 255);
}

void backward() {
    ledcWrite(MOTOR_CHANNEL_1, 255);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 255);
    ledcWrite(MOTOR_CHANNEL_4, 0); 
}

void left() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 255);
    ledcWrite(MOTOR_CHANNEL_3, 255);
    ledcWrite(MOTOR_CHANNEL_4, 0);  
}

void right() {
    ledcWrite(MOTOR_CHANNEL_1, 255);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 255);  
}

void stop() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 0);  
}

void initWebSocket() {
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len, uint32_t id) {
    char* str;
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    *(data + len) = 0;

    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        str = (char*)data;
        Serial.printf("websocket[%d]: \n%s\n", len, str);
        int value = (int)*(str) - 48;
        
        switch (value) {
            case 0:
                stop();
                break;

            case 1:
                forward();
                break;

            case 2:
                backward();
                break;

            case 3:
                left();
                break;

            case 4:
                right();
                break;

            default:
                break;
        }
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;

        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;

        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len, client->id());
            break;

        case WS_EVT_PONG:
        case WS_EVT_ERROR:
        default:
            break;
    }
}
