#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#include "conf/conf.h"

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

bool oled_setup  (Adafruit_SSD1306* display);

void showLogo    (Adafruit_SSD1306* display, const char* esp_ip_address, const char* esp_mdns);

void showWiFi    (Adafruit_SSD1306* display, const char* esp_ip_address, const char* esp_mdns);
void showAP      (Adafruit_SSD1306* display, const char* esp_ip_address, const char* esp_mdns);

void showAuto    (Adafruit_SSD1306* display, const char* esp_ip_address, const char* esp_mdns);
void showControl (Adafruit_SSD1306* display, const char* esp_ip_address, const char* esp_mdns);
void showUpdate  (Adafruit_SSD1306* display, const char* esp_ip_address, const char* esp_mdns);


void showImage(Adafruit_SSD1306* display, const uint8_t *, const char* esp_ip_address, const char* esp_mdns);
