#include <Arduino.h>

#include <EEPROM.h>

#define EEPROM_SIZE 512

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    if(!EEPROM.begin(EEPROM_SIZE)) {
        Serial.printf("EEPROM begin failed.\n");
    } else {
        Serial.printf("ESP32 start to clean EEPROM.\n");
        for(int i = 0; i < EEPROM_SIZE; i++) {
            EEPROM.write(i, 255);
        }
    }

    EEPROM.commit();
    Serial.printf("ESP32 clean EEPROM Finish.\n");

    Serial.printf("ESP32 check EEPROM data.\n");
    for(int i = 0; i < EEPROM_SIZE; i++) {
        if((i % 10) == 0) {
            Serial.printf("\n");
        }
        Serial.printf("%d ", EEPROM.read(i));
    }
    
    Serial.printf("\n");
    Serial.printf("ESP32 finish check EEPROM data.\n");
}

void loop() {

}
