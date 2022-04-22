#include <Arduino.h>

#define MOTOR_A01 13
#define MOTOR_A02 15
#define MOTOR_B01 14
#define MOTOR_B02 12

#define MOTOR_CHANNEL_1 0x01
#define MOTOR_CHANNEL_2 0x02
#define MOTOR_CHANNEL_3 0x03
#define MOTOR_CHANNEL_4 0x04

#define MOTOR_FREQ        5000
#define MOTOR_RESOLUTION     8

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    ledcSetup(MOTOR_CHANNEL_1, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_2, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_3, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_4, MOTOR_FREQ, MOTOR_RESOLUTION);

    ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_1);
    ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_2);
    ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_3);
    ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_4);

    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 0);
}

void loop() {
    for(int i = 0; i <= 255; i++) {
        ledcWrite(MOTOR_CHANNEL_1, i);
        Serial.printf("[Left] A01 forward: %d\n", i);
        delay(30);
    }
    ledcWrite(MOTOR_CHANNEL_1, 0);
    delay(1000);

    for(int i = 0; i <= 255; i++) {
        ledcWrite(MOTOR_CHANNEL_2, i);
        Serial.printf("[Left] A02 backward: %d\n", i);
        delay(30);
    }
    ledcWrite(MOTOR_CHANNEL_2, 0);
    delay(1000);

    for(int i = 0; i <= 255; i++) {
        ledcWrite(MOTOR_CHANNEL_3, i);
        Serial.printf("[Right] B01 forward: %d\n", i);
        delay(30);
    }
    ledcWrite(MOTOR_CHANNEL_3, 0);
    delay(1000);

    for(int i = 0; i <= 255; i++) {
        ledcWrite(MOTOR_CHANNEL_4, i);
        Serial.printf("[Right] B02 backward: %d\n", i);
        delay(30);
    }
    ledcWrite(MOTOR_CHANNEL_4, 0);
    delay(1000);
}