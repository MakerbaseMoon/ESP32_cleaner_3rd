#include "spiffs/spiffs.h"

bool spiffs_setup() {
    if(!SPIFFS.begin()){ 
        Serial.printf("An Error has occurred while mounting SPIFFS\n");  
        return false;
    }

    return true;
}

int get_spiffs_version() {
    File file = SPIFFS.open("/version.txt");

    if(!file){
        Serial.printf("Failed to open file for reading.\n");
        return -1;
    }
    
    char *_data = NULL;
    _data = (char *)malloc(10 * sizeof(char));
    if(_data == NULL) {
        Serial.printf("Failed to calloc data.\n");
        return -1;
    }

    size_t i = 0;
    while(file.available()){
        *(_data + i++) = (char)file.read();
    }
    *(_data + i) = 0;
    file.close();

    int num = char_pointer_to_int(_data);
    
    free(_data);
    _data = NULL;

    return num;
}

int char_pointer_to_int(const char* _data) {
    size_t i = 0;
    int num = 0;
    do {
        num *= 10;
        num += (*(_data + i++) - 48);
    } while(*(_data + i));

    return num;
}