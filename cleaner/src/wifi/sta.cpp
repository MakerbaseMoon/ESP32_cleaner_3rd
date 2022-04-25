#include "wifi/wifi.h"

void wifi_sta_mode(char* ssid, char* passwd, int *wifi_mode, char** esp_ip_address) {
    WiFi.mode(WIFI_STA);

    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("Your SSID: %s\n", ssid);
    Serial.printf("Your Password: %s\n", (passwd == NULL)? "NULL" : passwd);
    #endif

    wifi_sta_connect(ssid, passwd);

    size_t count = 0;

    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("Connetcing to %s...\n", ssid);
    #endif
    while(WiFi.status() != WL_CONNECTED && count++ < 20) {
        if(count == 10)
            wifi_sta_connect(ssid, passwd);
        delay(500);
    }

    if(WiFi.status() != WL_CONNECTED) {
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("Failed connect to WiFi, change AP mode.\n");
        #endif
        WiFi.disconnect();
        wifi_ap_mode(true, esp_ip_address);
        return;
    }

    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("Connetcing to %s susses.\n", ssid);
    #endif
    *wifi_mode = 1;

    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("ESP32 IP address: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("ESP32 IP mdns:    http://%s.local/\n", ESP32_MDNS_NAME);
    #endif
    get_esp32_ip_address(WiFi.localIP().toString().c_str(), esp_ip_address);
}

void wifi_sta_connect(char* ssid, char* passwd) {
    WiFi.disconnect();

    if(passwd == NULL)
        WiFi.begin(ssid);
    else
        WiFi.begin(ssid, passwd);
}

