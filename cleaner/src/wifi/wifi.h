#include <Arduino.h>

#include <WiFi.h>

#include <EEPROM.h>

#include <ESPmDNS.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "SPIFFS.h"

#include "eeprom/eeprom.h"
#include "conf/authentication.h"
#include "ota/ota.h"

#include "module/fan/fan.h"
#include "module/motor/motor.h"
#include "mode/mode.h"

void wifi_setup                 (char* ssid, char* passwd, AsyncWebServer* server, AsyncWebSocket* ws, int *mode, int *wifi_mode, char** url, char** esp_ip_address);

void wifi_ap_mode               (bool isPasswd , char** esp_ip_address);
void wifi_sta_mode              (char* ssid, char* passwd, int *wifi_mode, char** esp_ip_address);

void wifi_sta_connect           (char* ssid, char* passwd);

bool get_esp32_ip_address       (const char* esp_ip_address, char** esp_ip_address_pointer);

void initWebServer              (AsyncWebServer* server, int *mode, char** url, char* ssid);
void server_on_http             (AsyncWebServer* server);
int  set_server_post_eeprom_data(AsyncWebServerRequest *request);
void server_set_update          (AsyncWebServerRequest *request);
void server_get_url             (const char* url);

void initWebSocket              (AsyncWebServer* server, AsyncWebSocket* ws, int *mode);
void handleWebSocketMessage     (void*, uint8_t*, size_t, uint32_t);
void onEvent                    (AsyncWebSocket*, AsyncWebSocketClient*, AwsEventType, void*, uint8_t*, size_t);
