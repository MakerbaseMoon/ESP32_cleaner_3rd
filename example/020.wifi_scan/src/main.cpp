#include <Arduino.h>

#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    Serial.printf("\n\n");
}

void loop() {
    int16_t wifiNum = WiFi.scanNetworks();

    if(wifiNum == 0) {
        Serial.printf("ESP32 not found any WiFi.\n");

    } else {
        Serial.printf("ESP32 found %d WiFi.\n", wifiNum);

        for (size_t i = 0; i < wifiNum; i++) {
            Serial.printf("[%d] %s\t%d\t", (i + 1), WiFi.SSID(i).c_str(), (100 + (int)WiFi.RSSI(i)));

            switch (WiFi.encryptionType(i)) {
                case WIFI_AUTH_OPEN:
                    Serial.printf("OPEN\n");
                    break;

                case WIFI_AUTH_WEP:
                    Serial.printf("WEP\n");
                    break;

                case WIFI_AUTH_WPA_PSK:
                    Serial.printf("WPA PSK\n");
                    break;

                case WIFI_AUTH_WPA2_PSK:
                    Serial.printf("WPA2 PSK\n");
                    break;

                case WIFI_AUTH_WPA_WPA2_PSK:
                    Serial.printf("WPA WPA2 PSK\n");
                    break;

                case WIFI_AUTH_WPA2_ENTERPRISE:
                    Serial.printf("WPA2 ENTERPRISE\n");
                    break;

                default:
                    Serial.printf("Error\n");
                    break;
            } 
        }
    }
    Serial.printf("\n");
    delay(5000);
}

/** 
 * WiFi.encryptionType()
 *
 * WIFI_AUTH_OPEN = 0,         < authenticate mode : open 
 * WIFI_AUTH_WEP,              < authenticate mode : WEP 
 * WIFI_AUTH_WPA_PSK,          < authenticate mode : WPA_PSK 
 * WIFI_AUTH_WPA2_PSK,         < authenticate mode : WPA2_PSK 
 * WIFI_AUTH_WPA_WPA2_PSK,     < authenticate mode : WPA_WPA2_PSK 
 * WIFI_AUTH_WPA2_ENTERPRISE,  < authenticate mode : WPA2_ENTERPRISE 
 * 
**/
