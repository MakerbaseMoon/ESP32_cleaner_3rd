# ESP32 cleaner 3rd 

ESP32 路徑規劃掃地機 - 第三代.<br>
This is the cleaner project for maker.

* Group: 望月智聯網研究團隊
* Member: [jlhsu666](https://github.com/jlhsu666), [Hsun1031](https://github.com/Hsun1031), [Reaxoh](https://github.com/Reaxoh)

# Download (專案下載方式)

1. 點選右上角Code, Download ZIP檔案
2. 解壓縮ZIP檔
3. 下載 [lib](https://github.com/Hsun1031/ESP32_cleaner_3rd#project-libraries-%E5%B0%88%E6%A1%88-libraries) 並且放入 [ESP32_cleaner_3rd/cleaner/lib](https://github.com/Hsun1031/ESP32_cleaner_3rd/tree/master/cleaner/lib) (共6個libraries)
4. 將 [ESP32_cleaner_3rd/cleaner/src/conf/authentication-example.txt](https://github.com/Hsun1031/ESP32_cleaner_3rd/blob/master/cleaner/src/conf/authentication-example.txt) 改名為 ESP32_cleaner_3rd/cleaner/src/conf/authentication.h
5. 設定 ESP32_cleaner_3rd/cleaner/src/conf/authentication.h 的參數
6. 完成

## git command (git 指令)

```
git clone https://github.com/Hsun1031/ESP32_cleaner_3rd.git
git submodule update --init --recursive
``` 

## project files (專案檔案)

* build
* cleaner
* example
* kicad
* .gitignore
* .gitmodules
* README.md

## ESP32 Development Environments (ESP32 開發工具及環境)

* Install CP210x USB to UART Bridge VCP
  * <https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers>
* Install Visual Studio Code
  * <https://code.visualstudio.com/download>
* Connect to ESP32 website
  * <https://github.com/espressif/arduino-esp32>

## project libraries (專案 libraries)
* ESP32GithubOTA
  * <https://github.com/Hsun1031/ESP32GithubOTA>
* Adafruit_BusIO-master
  * <https://github.com/adafruit/Adafruit_BusIO>
* Adafruit_SSD1306-master
  * <https://github.com/adafruit/Adafruit_SSD1306>
* Adafruit-GFX-Library-master
  * <https://github.com/adafruit/Adafruit-GFX-Library>
* AsyncTCP-master
  * <https://github.com/me-no-dev/AsyncTCP>
* ESPAsyncWebServer-master
  * <https://github.com/me-no-dev/ESPAsyncWebServer>
