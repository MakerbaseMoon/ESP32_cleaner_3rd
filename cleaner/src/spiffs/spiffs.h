#include <Arduino.h>

#include "SPIFFS.h"

#include "conf/conf.h"

bool spiffs_setup();

int get_spiffs_version();

int char_pointer_to_int(const char* _data);
