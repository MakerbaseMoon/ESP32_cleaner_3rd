#include "eeprom/eeprom.h"

void set_SPIFFS_update(uint8_t data) {
    EEPROM.write(EEPROM_SPIFFS_UPDATE, data);
    EEPROM.commit();
}

uint8_t get_SPIFFS_update() {
    return EEPROM.read(EEPROM_SPIFFS_UPDATE);
}
