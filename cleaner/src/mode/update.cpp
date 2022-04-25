#include "mode/mode.h"

void update_firmware_mode(const char* url) {
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("firmware url: %s\n", url);
    #endif
    int error = cleaner_firmware_update(url, NULL);
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("ESP32 OTA Error code: %d\n", error);
    #endif
    if(!error) {
        set_SPIFFS_update(1);
        ESP.restart();
    } else {
        stop_mode();
    }
}

void update_spiffs_mode  (const char* url) {
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("spiffs url: %s\n", url);
    #endif
    int error = cleaner_spiffs_update(url, NULL);
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("ESP32 OTA Error code: %d\n", error);
    #endif
    if(!error)
        ESP.restart();
    else {
        stop_mode();
    }
}