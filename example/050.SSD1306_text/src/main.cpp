#include <Arduino.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 

void setup() {
    Serial.begin (115200);
    Serial.printf("\n\n");

    if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.printf("[Failed] SSD1306 OLED begin Error.\n");
        while(1);
    }

    display.clearDisplay();
		display.setTextColor(WHITE);
    display.setCursor(0, 0);
		display.setTextSize(1);
		display.printf("Hello World\n");
    display.setTextSize(2);
		display.printf("Hello World\n");
    display.setTextSize(3);
		display.printf("Hello World\n");
		display.display();
}

void loop() {

}
