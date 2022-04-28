#include "module/motor/motor.h"

void motor_setup(char* motor_pin) {
    ledcSetup(MOTOR_CHANNEL_1, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_2, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_3, MOTOR_FREQ, MOTOR_RESOLUTION);
    ledcSetup(MOTOR_CHANNEL_4, MOTOR_FREQ, MOTOR_RESOLUTION);

    if(motor_pin == NULL) {
        ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_1);
        ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_2);
        ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_3);
        ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_4);

        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("motor_pin: NULL\n");
        Serial.printf("MOTOR_CHANNEL_1: %d\n", MOTOR_A01);
        Serial.printf("MOTOR_CHANNEL_2: %d\n", MOTOR_A02);
        Serial.printf("MOTOR_CHANNEL_3: %d\n", MOTOR_B01);
        Serial.printf("MOTOR_CHANNEL_4: %d\n", MOTOR_B02);
        #endif

    } else if(*motor_pin == 48){
        ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_1);
        ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_2);
        ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_3);
        ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_4);

        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("motor_pin: 48\n");
        Serial.printf("MOTOR_CHANNEL_1: %d\n", MOTOR_A01);
        Serial.printf("MOTOR_CHANNEL_2: %d\n", MOTOR_A02);
        Serial.printf("MOTOR_CHANNEL_3: %d\n", MOTOR_B01);
        Serial.printf("MOTOR_CHANNEL_4: %d\n", MOTOR_B02);
        #endif

    } else if(*motor_pin == 49){
        ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_1);
        ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_2);
        ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_3);
        ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_4);

        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("motor_pin: 49\n");
        Serial.printf("MOTOR_CHANNEL_1: %d\n", MOTOR_A02);
        Serial.printf("MOTOR_CHANNEL_2: %d\n", MOTOR_A01);
        Serial.printf("MOTOR_CHANNEL_3: %d\n", MOTOR_B01);
        Serial.printf("MOTOR_CHANNEL_4: %d\n", MOTOR_B02);
        #endif

    } else if(*motor_pin == 50){
        ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_1);
        ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_2);
        ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_3);
        ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_4);

        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("motor_pin: 50\n");
        Serial.printf("MOTOR_CHANNEL_1: %d\n", MOTOR_A01);
        Serial.printf("MOTOR_CHANNEL_2: %d\n", MOTOR_A02);
        Serial.printf("MOTOR_CHANNEL_3: %d\n", MOTOR_B02);
        Serial.printf("MOTOR_CHANNEL_4: %d\n", MOTOR_B01);
        #endif

    } else if(*motor_pin == 51){
        ledcAttachPin(MOTOR_A02, MOTOR_CHANNEL_1);
        ledcAttachPin(MOTOR_A01, MOTOR_CHANNEL_2);
        ledcAttachPin(MOTOR_B02, MOTOR_CHANNEL_3);
        ledcAttachPin(MOTOR_B01, MOTOR_CHANNEL_4);

        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("motor_pin: 51\n");
        Serial.printf("MOTOR_CHANNEL_1: %d\n", MOTOR_A02);
        Serial.printf("MOTOR_CHANNEL_2: %d\n", MOTOR_A01);
        Serial.printf("MOTOR_CHANNEL_3: %d\n", MOTOR_B02);
        Serial.printf("MOTOR_CHANNEL_4: %d\n", MOTOR_B01);
        #endif
    }
}

void motor_mode0() {
    motor_mode(0b0000);
}

void motor_mode1() {
    motor_mode(0b1010);
}

void motor_mode2() {
    motor_mode(0b0101);
}

void motor_mode3() {
    motor_mode(0b0110);
}

void motor_mode4() {
    motor_mode(0b1001);
}

/**
 * @brief set motor ledc.
 * 
 * 0b0000 // stop   -> 0
 * 0b1010 // go     -> 10
 * 0b0101 // back   -> 5
 * 0b0110 // left   -> 6
 * 0b1001 // right  -> 9
 * 
 * @param mode 
 */
void motor_mode(int8_t mode) {
    ledcWrite(MOTOR_CHANNEL_1, ((mode >> 3) & 1)? MOTOR_A01_LEDC_MAX : MOTOR_STOP);
    ledcWrite(MOTOR_CHANNEL_2, ((mode >> 2) & 1)? MOTOR_A02_LEDC_MAX : MOTOR_STOP);
    ledcWrite(MOTOR_CHANNEL_3, ((mode >> 1) & 1)? MOTOR_A03_LEDC_MAX : MOTOR_STOP);
    ledcWrite(MOTOR_CHANNEL_4, ((mode >> 0) & 1)? MOTOR_A04_LEDC_MAX : MOTOR_STOP);
}
