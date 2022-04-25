#include "wifi/wifi.h"

void wifi_setup(char* ssid, char* passwd, AsyncWebServer* server, AsyncWebSocket* ws, int *mode, int *wifi_mode, char** url, char** esp_ip_address) {
    if(ssid == NULL)
        wifi_ap_mode(true, esp_ip_address);
    else
        wifi_sta_mode(ssid, passwd, wifi_mode, esp_ip_address);

    if(!MDNS.begin(ESP32_MDNS_NAME)) {
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("Error starting mDNS.\n");
        #endif
    }
    
    initWebServer(server, mode, url, ssid);
    initWebSocket(server, ws, mode);

    server->begin();
}

bool get_esp32_ip_address(const char* esp_ip_address, char** esp_ip_address_pointer) {
    size_t i = 0;
    while(*(esp_ip_address + i++));
    *esp_ip_address_pointer = (char *)malloc(i * sizeof(char));

    if(*esp_ip_address_pointer == NULL)
        return false;

    while(1 + i--) {
        *(*esp_ip_address_pointer + i) = *(esp_ip_address + i);
    }

    return true;
}