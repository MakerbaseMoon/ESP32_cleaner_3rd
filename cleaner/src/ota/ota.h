#include <Arduino.h>
#include <ESP32GithubOTA.h>

#include "conf/conf.h"
#include "spiffs/spiffs.h"
#include "eeprom/eeprom.h"
#include "conf/authentication.h"
#include "module/oled/oled.h"

void  check_cleaner_spiffs_version  (int *wifi_mode, Adafruit_SSD1306 *display);

int cleaner_firmware_update(const char* githubUrl, char* token);
int cleaner_spiffs_update  (const char* githubUrl, char* token);
