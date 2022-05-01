#include "cleaner.h"

int mode      = 0;
int wifi_mode = 0;

char *ssid   = NULL;
char *passwd = NULL;

char *url    = NULL;

char *json   = NULL;

char *esp_ip_address = NULL;
char *esp_mdns       = NULL;

char*  motor_pin  = NULL;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // create Adafruit SSD1306 Object.

AsyncWebServer server (80);    // create HTTP Object.
AsyncWebSocket ws     ("/ws"); // create WebSocket Object.

void setup() {
    Serial.begin (115200); // Sets the data rate in bits per second (baud) for serial data transmission.
    Serial.printf("\n\n"); // Newline.

    oled_setup  (&display);                              // SSD1306 OLED setup.
    eeprom_setup(&ssid, &passwd, &esp_mdns, &motor_pin); // ESP32 EEPROM setup.
    spiffs_setup();                                      // SPIFFS setup.
    motor_setup (motor_pin);                            // MX1508 Motor setup.
    fan_setup   ();                                      // Fan MOS module setup.

    wifi_setup  (ssid, passwd, &server, &ws, &mode, &wifi_mode, &url, &esp_ip_address, motor_pin); // WiFi setup.

    check_cleaner_spiffs_version(&wifi_mode, &display); // check cleaner spiffs version.
    
    auto_begin  (); // Ready ro start auto mode.
}

void loop() {
    switch (mode) {
        case 0: // Auto Mode
            auto_mode   (&display, &wifi_mode, esp_ip_address, esp_mdns, &mode);
            break;

        case 1: // Control Mode
            control_mode(&display, &wifi_mode, esp_ip_address, esp_mdns);
            break;

        case 2: // Firmware Update Mode
            showUpdate(&display, NULL, NULL);
            update_firmware_mode(url);
            mode = 1;
            break;

        // case 3: // SPIFFS Update Mode
        //     showUpdate(&display, NULL, NULL);
        //     update_spiffs_mode(url);
        //     mode = 1;
        //     break;

        default:
            break;
    }

    ws.cleanupClients(); // Clean websocket disconnect clients.

    delay(30); // delay 0.03s
}
