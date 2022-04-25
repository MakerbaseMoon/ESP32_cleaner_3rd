#include "eeprom/eeprom.h"

bool eeprom_setup(char** ssid, char** passwd, char** esp_mdns) {
    if(!EEPROM.begin(512)) {                        // setup EEPROM.
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("Error to start EEPROM\n");   // EEPROM Error.
        #endif
        return false;
    }

    if(!get_ssid(ssid)) {
        free(*ssid);
        *ssid = NULL;
    }
        
    if(!get_passwd(passwd)) {
        free(*passwd);
        *passwd = NULL;
    }

    if(!get_esp_mdns(esp_mdns)) {
        free(*esp_mdns);
        *esp_mdns = NULL;
        const char* esp_default_mdns = ESP32_MDNS_NAME;
        size_t i = 0;
        while(*(esp_default_mdns + i++));
        *esp_mdns = (char *)malloc(i * sizeof(char));
        if(*esp_mdns == NULL) {
            *esp_mdns = NULL;
        }else {
            while(1 + i--) {
                *(*esp_mdns + i) = *(esp_default_mdns + i);
            }
        }
    }

    return true;
}

bool set_esp_mdns  (const char* mdns) {
    return set_eeprom_data(EEPROM_MDNS_START, EEPROM_MDNS_END, (uint8_t *)mdns);
}

bool set_github_token(const char* token) {
    return set_eeprom_data(EEPROM_TOKEN_START, EEPROM_TOKEN_END, (uint8_t *)token);
}

bool get_esp_mdns  (char**  mdns) {
    if(!is_eeprom_data(EEPROM_MDNS_START))
        return false;

    return get_eeprom_data(EEPROM_MDNS_START, (uint8_t **)mdns);
}

bool get_github_token(char** token) {
    if(!is_eeprom_data(EEPROM_TOKEN_START))
        return false;

    return get_eeprom_data(EEPROM_TOKEN_START, (uint8_t **)token);
}
