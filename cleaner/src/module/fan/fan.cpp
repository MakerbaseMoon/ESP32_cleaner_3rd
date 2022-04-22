#include "module/fan/fan.h"

void fan_setup() {
    ledcSetup(FAN_CHANNEL_5, FAN_FREQ, FAN_RESOLUTION);

    ledcAttachPin(FAN_FAN, FAN_CHANNEL_5);
}

void fan_mode(int8_t mode) {
    int ledc_value = 25 + mode * 75;
    ledc_value = (ledc_value >= 255)? 255 : (ledc_value < 100 )? 0 : ledc_value;
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("Fan PWM: %d\n", ledc_value);
    #endif
    ledcWrite(FAN_CHANNEL_5, ledc_value);
}
