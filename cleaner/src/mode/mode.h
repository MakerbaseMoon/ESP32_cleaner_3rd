#include <Arduino.h>

#include "module/motor/motor.h"
#include "module/fan/fan.h"

#include "ota/ota.h"
#include "module/oled/oled.h"

void auto_begin();
void auto_mode(Adafruit_SSD1306* _display, int *wifi_mode, const char* esp_ip_address, const char* esp_mdns);

void stop_mode();

void update_firmware_mode(const char* url);
void update_spiffs_mode  (const char* url);

void control_mode(Adafruit_SSD1306* _display, int *wifi_mode, const char* esp_ip_address, const char* esp_mdns);
