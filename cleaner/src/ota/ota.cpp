#include "ota/ota.h"

float check_cleaner_firmware_version() {
    return ESP32_CLEANER_FIRMWARE_VERSION;
}

void check_cleaner_spiffs_version(int *wifi_mode, Adafruit_SSD1306 *display) { 
    if(!(*wifi_mode))
        return;
        
    int spiffs_version = get_spiffs_version();
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("[Now] ESP32 Spiffs Now version: %d\n", spiffs_version);
    Serial.printf("[New] ESP32 Spiffs New version: %d\n", ESP32_CLEANER_SPIFFS_VERSION);
    #endif
    if(spiffs_version != ESP32_CLEANER_SPIFFS_VERSION) {
        showUpdate(display, NULL, NULL);
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[Update] ESP32 will Update New Spiffs version: %d\n", ESP32_CLEANER_SPIFFS_VERSION);
        #endif
        int error_code = cleaner_spiffs_update(GITHUB_SPIFFS_BIN_URL, NULL);
        if(!error_code) {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("[Susses] ESP32 is allready Update last Spiffs version: %d\n", spiffs_version);
            #endif
            ESP.restart();
        } else {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("[Failed][Code: %d] ESP32 Failed Update Spiffs version: %d\n", error_code, spiffs_version);
            #endif
        }
        showLogo(display, NULL, NULL);
    } else {
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[Allready] ESP32 is allready Update last Spiffs version: %d\n", ESP32_CLEANER_SPIFFS_VERSION);
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
