#include "wifi/wifi.h"

int *  _mode = NULL;
char** _url  = NULL;
char*  _ssid = NULL;

void initWebServer(AsyncWebServer* server, int *mode, char** url, char* ssid) {
    _mode = mode;
    _url  = url;
    _ssid = ssid;

    server_on_http(server);

    server->on("/set/data", HTTP_POST, [](AsyncWebServerRequest *request) {
        int error_code = set_server_post_eeprom_data(request);
        if(error_code) {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("ESP32 Set data error: %d\n", error_code);
            #endif
            request->send(200, "text/plain", "Error");
        } else {
            request->send(200, "text/plain", "OK");
        }

        ESP.restart();
    });

    server->on("/get/version", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", ESP32_CLEANER_VERSION);
    });

    server->on("/get/wifi/ssid", HTTP_POST, [](AsyncWebServerRequest *request) {
        if(_ssid == NULL) {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("[POST] WiFi SSID : NULL\n");
            #endif
            request->send(200, "text/plain", "NULL");
        } else {
            #ifdef ESP32_CLEANER_SHOW_DEBUG
            Serial.printf("[POST] WiFi SSID : %s\n", _ssid);
            #endif
            request->send(200, "text/plain", _ssid);
        }   
    });

    server->on("/get/githubjson", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", GITHUB_VERSION_JSON_URL);
    });

    server->on("/ota/update", HTTP_POST, [](AsyncWebServerRequest *request) {
        stop_mode();
        server_set_update(request);
        request->send(200, "text/plain", "OK");
    });

    server->on("/set/mode", HTTP_POST, [](AsyncWebServerRequest *request) {
        int change_mode = (int)*(request->getParam(0)->value().c_str()) - 48;
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("ESP32 Cleaner Mode: %d\n", change_mode);
        #endif
        if(change_mode == 0) {
            auto_begin();
            *_mode = 0;
        } else if(change_mode == 1) {
            stop_mode();
            *_mode = 1;
        }
        request->send(200, "text/plain", "OK");
    });

    server->on("/set/fan", HTTP_POST, [](AsyncWebServerRequest *request) {
        AsyncWebParameter *p = request->getParam(0);
        int fan_value = (int)(*p->value().c_str()) - 48;
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[Fan]%s: %s %d\n", p->name().c_str(), p->value().c_str(), fan_value);
        #endif
        fan_mode((int)(*p->value().c_str()) - 48);
        request->send(200, "text/plain", "OK");
    });

    server->on("/clean/eeprom", HTTP_POST, [](AsyncWebServerRequest *request) {
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[Clean] Clean eeprom data.\n");
        #endif
        clean_eeprom_data();
        request->send(200, "text/plain", "OK");
        ESP.restart();
    });

    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("cleaner server on.\n");
    #endif
}

void server_on_http(AsyncWebServer* server) {
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("PC client index.html\n");
        #endif
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server->on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/javascript/main.js", "text/javascript");
    });

    server->on("/github_form.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/javascript/github_form.js", "text/javascript");
    });

    server->on("/wifi_form.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/javascript/wifi_form.js", "text/javascript");
    });

    server->on("/fan.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/javascript/fan.js", "text/javascript");
    });

    server->on("/motor.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/javascript/motor.js", "text/javascript");
    });

    server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/css/style.css");
    });

    server->on("/bootstrap.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/bootstrap/bootstrap.css");
    });

    server->on("/bootstrap.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/bootstrap/bootstrap.js", "text/javascript");
    });

    server->on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/image/favicon.jpg", "image/jpg");
    });

    server->on("/background", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/image/background.jpg", "image/jpg");
    });
}

int set_server_post_eeprom_data(AsyncWebServerRequest *request) {
    size_t params = request->params();
    int server_post_eeprom_data_error_code = 0;

    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("POST:\n");
    #endif
    for (size_t i = 0; i < params; i++) {
        AsyncWebParameter *p = request->getParam(i);
        #ifdef ESP32_CLEANER_SHOW_DEBUG
        Serial.printf("[%d]%s: %s %d\n", (int)*(p->name().c_str()), p->name().c_str(), p->value().c_str(), (int)*(p->value().c_str()));
        #endif

        if(!(int)*(p->value().c_str()))
            continue;

        if((int)*(p->name().c_str()) == 48) { // 0
            if(set_ssid(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_ssid OK.\n");
                #endif
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_ssid Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 0);
            }
        }
        
        if((int)*(p->name().c_str()) == 49) { // 1
            if(set_passwd(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_passwd OK.\n");
                #endif            
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_passwd Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 1);
            }
        }

        if((int)*(p->name().c_str()) == 50) { // 2
            if(set_ap_ssid(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_ap_ssid OK.\n");
                #endif            
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_ap_ssid Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 2);
            }
        }

        if((int)*(p->name().c_str()) == 51) { // 3
            if(set_ap_passwd(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_ap_passwd OK.\n");
                #endif            
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_ap_passwd Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 3);
            }
        }

        if((int)*(p->name().c_str()) == 52) { // 4
            if(set_esp_mdns(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_esp_mdns OK.\n");
                #endif            
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_esp_mdns Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 4);
            }
        }

        if((int)*(p->name().c_str()) == 53) { // 5
            if(set_github_token(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_github_token OK.\n");
                #endif            
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_github_token Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 5);
            }
        }

        if((int)*(p->name().c_str()) == 54) { // 6
            if(set_motor_pin(p->value().c_str())) {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_motor_pin OK.\n");
                #endif            
            } else {
                #ifdef ESP32_CLEANER_SHOW_DEBUG
                Serial.printf("set_motor_pin Error.\n");
                #endif
                server_post_eeprom_data_error_code += (1 << 6);
            }
        }
    }

    return server_post_eeprom_data_error_code;
}

void server_set_update(AsyncWebServerRequest *request) {
    int name  = (int)*(request->getParam(0)->name(). c_str()) - 48;
  
    if(name == 4) {
        // server_get_url(GITHUB_FIRMWARE_BIN_URL);
        // name = 2;
    } else {
        server_get_url(request->getParam(0)->value().c_str());
    }

    *_mode = name;
}

void server_get_url(const char* url) {
    size_t k = 0;
    size_t i = 0;

    while((int)*(url + k++));

    *_url = (char *)malloc(k * sizeof(char));
    
    k = 0;

    do {
        i = (int)*(url + k);
        *(*_url + k) = (char)i;
        k++;
    } while (i);
    
    #ifdef ESP32_CLEANER_SHOW_DEBUG
    Serial.printf("firmware url update: %s\n", *_url);
    #endif
}