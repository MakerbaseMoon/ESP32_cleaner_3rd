#include <Arduino.h>

#include "conf/conf.h"

#define MOTOR_A01 (CLEANER_A01)
#define MOTOR_A02 (CLEANER_A02)
#define MOTOR_B01 (CLEANER_B01)
#define MOTOR_B02 (CLEANER_B02)

#define MOTOR_CHANNEL_1 0x01
#define MOTOR_CHANNEL_2 0x02
#define MOTOR_CHANNEL_3 0x03
#define MOTOR_CHANNEL_4 0x04

#define MOTOR_FREQ        5000
#define MOTOR_RESOLUTION     8

#define MOTOR_A01_LEDC_MAX 255
#define MOTOR_A02_LEDC_MAX 255
#define MOTOR_A03_LEDC_MAX 255
#define MOTOR_A04_LEDC_MAX 255

#define MOTOR_STOP 0

void motor_setup();

void motor_mode0();
void motor_mode1();
void motor_mode2();
void motor_mode3();
void motor_mode4();

void motor_mode(int8_t mode);
