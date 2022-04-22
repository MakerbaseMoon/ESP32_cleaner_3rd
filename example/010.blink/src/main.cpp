#include <Arduino.h>

int led = 2;

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    pinMode(led, OUTPUT);
}

void loop() {
    digitalWrite(led, HIGH);
    delay(1000);

    digitalWrite(led, LOW);
    delay(1000);
}
