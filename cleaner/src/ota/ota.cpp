#include "ota/ota.h"

void check_cleaner_spiffs_version(int *wifi_mode, Adafruit_SSD1306 *display) { 
    if(!(*wifi_mode))
        return;
    
    if(!get_SPIFFS_update()) {
        showUpdate(display, NULL, NULL);
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[Update] ESP32 will Update New Spiffs version: %s\n", ESP32_CLEANER_VERSION);
        #endif
        int error_code = cleaner_spiffs_update(GITHUB_SPIFFS_BIN_URL, NULL);
        if(!error_code) {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("[Susses] ESP32 is allready Update last Spiffs version: %s\n", ESP32_CLEANER_VERSION);
            #endif
            set_SPIFFS_update(0);
            ESP.restart();
        } else {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("[Failed][Code: %d] ESP32 Failed Update Spiffs version: %s\n", error_code, ESP32_CLEANER_VERSION);
            #endif
        }
        showLogo(display, NULL, NULL);
    } else {
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[Allready] ESP32 is allready Update last Spiffs version: %s\n", ESP32_CLEANER_VERSION);
        #endif
    }
}

int cleaner_firmware_update(const char* githubUrl, char* token = NULL) {
    ESP32PrivateGithubOTA ota(token);
    return ota.firmwareOTA(githubUrl);
}

int cleaner_spiffs_update  (const char* githubUrl, char* token = NULL) {
    ESP32PrivateGithubOTA ota(token);
    return ota.spiffsOTA(githubUrl);
}
