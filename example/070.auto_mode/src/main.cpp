#include <Arduino.h>

#define LEFT_WARNIMG_DISTANCE 3000
#define RIGHT_WARNIMG_DISTANCE 3000

#define LEFT_SAFE_DISTANCE 3200
#define RIGHT_SAFE_DISTANCE 3200

#define LEFT_IR 33 // left
#define RIGHT_IR 32 // right

#define FAN_PIN 17

#define FAN_CHANNEL 0x05

#define FAN_FREQ 5000
#define FAN_RESOLUTION 8

#define MOTOR_A01 13
#define MOTOR_A02 15
#define MOTOR_B01 14
#define MOTOR_B02 12

#define MOTOR_CHANNEL_1 0x01
#define MOTOR_CHANNEL_2 0x02
#define MOTOR_CHANNEL_3 0x03
#define MOTOR_CHANNEL_4 0x04

#define MOTOR_FREQ 5000
#define MOTOR_RESOLUTION 8

void forward();
void backward();
void left();
void right();
void stop();

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");

    ledcSetup(FAN_CHANNEL, FAN_FREQ, FAN_RESOLUTION);
    ledcAttachPin(FAN_PIN, FAN_CHANNEL);

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
    ledcWrite(FAN_CHANNEL, 255);

    forward();

}

void loop() {
    if(analogRead(RIGHT_IR) > RIGHT_WARNIMG_DISTANCE || analogRead(LEFT_IR) > LEFT_WARNIMG_DISTANCE) {
        forward();
        delay(300);

        stop();
        delay(100);

        backward();
        delay(500);

        if(analogRead(RIGHT_IR) > analogRead(LEFT_IR)) {
            left();
            delay(200);

            while(analogRead(RIGHT_IR) > RIGHT_SAFE_DISTANCE) {
                left();
            }

            stop();
            delay(100);

        } else {
            right();
            delay(300);

            while(analogRead(LEFT_IR) > LEFT_SAFE_DISTANCE) {
                right();
            }

            stop();
            delay(100);
        }
        forward();
    }
}

void forward() {
    ledcWrite(MOTOR_CHANNEL_1, 255);
    ledcWrite(MOTOR_CHANNEL_2, 0);
    ledcWrite(MOTOR_CHANNEL_3, 255);
    ledcWrite(MOTOR_CHANNEL_4, 0); 
}

void backward() {
    ledcWrite(MOTOR_CHANNEL_1, 0);
    ledcWrite(MOTOR_CHANNEL_2, 255);
    ledcWrite(MOTOR_CHANNEL_3, 0);
    ledcWrite(MOTOR_CHANNEL_4, 255);
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
