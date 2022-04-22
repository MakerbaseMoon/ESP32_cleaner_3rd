#include "wifi/wifi.h"

void initWebSocket(AsyncWebServer* server, AsyncWebSocket* ws, int *mode) {
    ws->onEvent       (onEvent);
    server->addHandler(ws);
}

void handleWebSocketMessage(void     *arg,
                            uint8_t  *data,
                            size_t    len,
                            uint32_t  id) {
    char* str;
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    *(data + len) = 0;

    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        str = (char*)data;
        Serial.printf("websocket[%d]: \n%s\n", len, str);
        int value = (int)*(str) - 48;
        
        switch (value) {
            case 0:
                motor_mode0();
                break;
            case 1:
                motor_mode1();
                break;
            case 2:
                motor_mode2();
                break;
            case 3:
                motor_mode3();
                break;
            case 4:
                motor_mode4();
                break;
            default:
                break;
        }
    }
}

void onEvent(AsyncWebSocket       *server, 
             AsyncWebSocketClient *client, 
             AwsEventType          type,
             void                 *arg, 
             uint8_t              *data, 
             size_t                len) {
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
            break;
    }
}
