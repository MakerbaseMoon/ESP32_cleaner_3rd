#include "mode/mode.h"

void stop_mode() {
    fan_mode(0);
    motor_mode0();
}
