#include <Arduino.h>

#define FAN_PIN 17

#define FAN_CHANNEL 1

#define FAN_FREQ 5000
#define FAN_RESOLUTION 8

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    ledcSetup(FAN_CHANNEL, FAN_FREQ, FAN_RESOLUTION);
    ledcAttachPin(FAN_PIN, FAN_CHANNEL);
}

void loop() {
    for(int i = 0; i <= 255; i++) {
        ledcWrite(FAN_CHANNEL, i);
        Serial.printf("duty: %d\n", i);
        delay(30);
    }
    delay(2000);

    for(int i = 255; i >= 0; i--) {
        ledcWrite(FAN_CHANNEL, i);
        Serial.printf("duty: %d\n", i);
        delay(30);
    }
    delay(2000);
}
