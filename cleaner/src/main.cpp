#include "cleaner.h"

int mode      = 0;
int wifi_mode = 0;

char *ssid   = NULL;
char *passwd = NULL;

char *url    = NULL;

char *json   = NULL;

char *esp_ip_address = NULL;
char *esp_mdns       = NULL;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create Adafruit SSD1306 Object.

AsyncWebServer server (80);    // create HTTP Object.
AsyncWebSocket ws     ("/ws"); // create WebSocket Object.

void setup() {
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.begin (115200); // Sets the data rate in bits per second (baud) for serial data transmission.
    Serial.printf("\n\n"); // Newline.
    #endif

    oled_setup  (&display);
    eeprom_setup(&ssid, &passwd, &esp_mdns);
    spiffs_setup();
    motor_setup ();
    fan_setup   ();
    wifi_setup  (ssid, passwd, &server, &ws, &mode, &wifi_mode, &url, &esp_ip_address);
    
    Serial.printf("esp_ip_address: %s\n", esp_ip_address);
    Serial.printf("esp_mdns:       %s\n", esp_mdns);

    check_cleaner_spiffs_version(&wifi_mode, &display); // check cleaner spiffs version.
    
    auto_begin  ();
}

void loop() {
    switch (mode) {
        case 0:
            auto_mode   (&display, &wifi_mode, esp_ip_address, esp_mdns);
            break;

        case 1:
            control_mode(&display, &wifi_mode, esp_ip_address, esp_mdns);
            break;

        case 2:
            showUpdate(&display, NULL, NULL);
            update_firmware_mode(url);
            mode = 1;
            break;

        case 3:
            showUpdate(&display, NULL, NULL);
            update_spiffs_mode(url);
            mode = 1;
            break;

        default:
            break;
    }

    delay(30);
}
