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

void forward();
void backward();
void left();
void right();
void stop();

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

    stop();
}

void loop() {
    forward();
    delay(3000);

    backward();
    delay(3000);

    left();
    delay(3000);

    right();
    delay(3000);
}

void forward() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 255);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 255);
}

void backward() {
    ledcWrite(MOTOR_CHANNEL_1, 255);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 255);
    ledcWrite(MOTOR_CHANNEL_4, 0); 
}

void left() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 255);
    ledcWrite(MOTOR_CHANNEL_3, 255);
    ledcWrite(MOTOR_CHANNEL_4, 0);  
}

void right() {
    ledcWrite(MOTOR_CHANNEL_1, 255);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 255);  
}

void stop() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 0);  
}