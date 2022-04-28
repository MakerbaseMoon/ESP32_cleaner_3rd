#include "eeprom/eeprom.h"

bool set_motor_pin(const char*  motor_pin) {
    set_eeprom_data(EEPROM_MOTOR_PIN_START, EEPROM_MOTOR_PIN_END, (uint8_t *)motor_pin);
}

bool get_motor_pin(char** motor_pin) {
    if(!is_eeprom_data(EEPROM_MOTOR_PIN_START))
        return false;

    return get_eeprom_data(EEPROM_MOTOR_PIN_START, (uint8_t **)motor_pin);
}
