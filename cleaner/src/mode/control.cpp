#include "mode/mode.h"

unsigned long control_time = 0;
int control_image = 0;

void control_mode(Adafruit_SSD1306* _display, int *wifi_mode, const char* esp_ip_address, const char* esp_mdns) {
    if((millis() - control_time) > 2000) {
        switch (control_image) {
            case 0:
                showLogo(_display, esp_ip_address, esp_mdns);
                control_image += 1;
                break;
            case 1:
                showControl(_display, esp_ip_address, esp_mdns);
                control_image += 1;
                break;
            case 2:
                if(*wifi_mode)
                    showWiFi(_display, esp_ip_address, esp_mdns);
                else
                    showAP(_display, esp_ip_address, esp_mdns);
                    
                control_image = 0;
                break;
            default:
                control_image = 0;
                break;
        }
        control_time = millis();
    }
}