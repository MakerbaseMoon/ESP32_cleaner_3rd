#include "wifi/wifi.h"

void wifi_ap_mode(bool isPasswd, char** esp_ip_address) {
    WiFi.mode(WIFI_AP);

    Serial.printf("Your ESP32 AP SSID:     %s\n", ESP_AP_SSID);
    Serial.printf("Your ESP32 AP Password: %s\n", ESP_AP_PASSWD);

    if(isPasswd)
        WiFi.softAP(ESP_AP_SSID, ESP_AP_PASSWD);
    else
        WiFi.softAP(ESP_AP_SSID);

    Serial.printf("ESP32 IP address: %s\n", WiFi.softAPIP().toString().c_str());
    Serial.printf("ESP32 IP mdns:    http://%s.local/\n", ESP32_MDNS_NAME);
    get_esp32_ip_address(WiFi.softAPIP().toString().c_str(), esp_ip_address);
}
