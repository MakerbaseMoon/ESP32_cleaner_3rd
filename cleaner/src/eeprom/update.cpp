#include "eeprom/eeprom.h"

void set_SPIFFS_update(uint8_t data) {
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("set_SPIFFS_update\n");
    #endif
    EEPROM.write(EEPROM_SPIFFS_UPDATE, data);
    EEPROM.commit();
}

uint8_t get_SPIFFS_update() {
    return EEPROM.read(EEPROM_SPIFFS_UPDATE);
}
