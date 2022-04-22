#include <Arduino.h>

int led = 2;

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    pinMode(led, OUTPUT);
}

void loop() {
    digitalWrite(led, HIGH);
    Serial.printf("LED ON\n");
    delay(1000);

    digitalWrite(led, LOW);
    Serial.printf("LED OFF\n");
    delay(1000);
}
