#include <Arduino.h>

#define LEFT_IR  33 // left
#define RIGHT_IR 32 // right

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");
}

void loop() {
    Serial.printf("%d %d\n", analogRead(RIGHT_IR), analogRead(LEFT_IR));
    delay(100);
}
