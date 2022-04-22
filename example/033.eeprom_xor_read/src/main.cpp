#include <Arduino.h>

#include <EEPROM.h>

#define EEPROM_SIZE 512

#define KEY 165

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

            int data =  EEPROM.read(i);
            if(data == 255) {
                Serial.printf("%d ", data);
            } else {
                Serial.printf("%d ", data ^ KEY);
            }
        }

        Serial.printf("\n\n");
        Serial.printf("ESP32 start to Read EEPROM (char).\n");
        for(int i = 0; i < EEPROM_SIZE; i++) {
            if((i % 10) == 0) {
                Serial.printf("\n");
            }

            int data =  EEPROM.read(i);
            if(data == 255) {
                Serial.printf("%c ", data);
            } else {
                Serial.printf("%c ", data ^ KEY);
            }
        }
    }

    Serial.printf("\n");
    Serial.printf("ESP32 Read EEPROM Finish.\n");
}

void loop() {

}
