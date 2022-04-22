#include <Arduino.h>

#include "conf/conf.h"

#define FAN_FAN       (FAN)
#define FAN_CHANNEL_5  0x05

#define FAN_FREQ       5000
#define FAN_RESOLUTION    8

void fan_setup();
void fan_mode(int8_t mode);
