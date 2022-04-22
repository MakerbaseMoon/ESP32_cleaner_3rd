#include <Arduino.h>

#include <EEPROM.h>

#define EEPROM_SIZE 512

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    if(!EEPROM.begin(EEPROM_SIZE)) {
        Serial.printf("EEPROM begin failed.\n");
    } else {
        Serial.printf("ESP32 start to Read EEPROM (int).\n");
        for(int i = 0; i < EEPROM_SIZE; i++) {
            if((i % 10) == 0) {
                Serial.printf("\n");
            }
            Serial.printf("%d ", EEPROM.read(i));
        }

        Serial.printf("\n\n");
        Serial.printf("ESP32 start to Read EEPROM (char).\n");
        for(int i = 0; i < EEPROM_SIZE; i++) {
            if((i % 10) == 0) {
                Serial.printf("\n");
            }
            Serial.printf("%c ", EEPROM.read(i));
        }
    }

    Serial.printf("\n");
    Serial.printf("ESP32 Read EEPROM Finish.\n");
}

void loop() {

}
