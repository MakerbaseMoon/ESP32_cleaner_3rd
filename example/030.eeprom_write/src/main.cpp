#include <Arduino.h>

#include <EEPROM.h>

#define EEPROM_SIZE 512

#define STR_LEN 13

int start = 10;

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    const char str[STR_LEN] = "Hello world!";

    if(!EEPROM.begin(EEPROM_SIZE)) {
        Serial.printf("EEPROM begin failed.\n");
    } else {
        Serial.printf("ESP32 start to flash EEPROM.\n");
        for(int i = 0; i < STR_LEN; i++) {
            EEPROM.write(i + start, str[i]);
        }
    }

    EEPROM.commit();
    Serial.printf("ESP32 flash EEPROM Finish.\n");
}

void loop() {

}
