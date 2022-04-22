#include "mode/mode.h"

void update_firmware_mode(const char* url) {
    Serial.printf("firmware url: %s\n", url);
    int error = cleaner_firmware_update(url, NULL);
    Serial.printf("ESP32 OTA Error code: %d\n", error);
    if(!error)
        ESP.restart();
    else {
        stop_mode();
    }
}

void update_spiffs_mode  (const char* url) {
    Serial.printf("spiffs url: %s\n", url);
    int error = cleaner_spiffs_update(url, NULL);
    Serial.printf("ESP32 OTA Error code: %d\n", error);
    if(!error)
        ESP.restart();
    else {
        stop_mode();
    }
}