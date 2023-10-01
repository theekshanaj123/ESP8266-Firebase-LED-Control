# ESP8266 Firebase LED Control

This Arduino sketch demonstrates how to use an ESP8266 WiFi module to connect to Firebase and control an LED based on data from the Firebase Realtime Database (RTDB).

## Prerequisites

Before you begin, make sure you have the following:

- An Arduino board with an ESP8266 WiFi module.
- The Arduino IDE installed on your computer.
- The required libraries installed:
  - `ESP8266WiFi`
  - `Firebase_ESP_Client`
  - `WiFiManager`

## Installation

1. Clone or download this repository to your local machine.
2. Open the Arduino IDE.
3. Go to **File > Preferences** and add the following URL to the Additional Boards Manager URLs: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
4. Go to **Tools > Board > Boards Manager**, search for "ESP8266," and install the "esp8266" platform.
5. Select the appropriate ESP8266 board from **Tools > Board**.
6. In the Arduino IDE, open the `ESP8266_Firebase_LED_Control.ino` sketch from the downloaded repository.
7. Configure your network credentials and Firebase API key by modifying the following lines in the sketch:

   ```cpp
   #define API_KEY "YOUR_FIREBASE_API_KEY"
   #define DATABASE_URL "YOUR_FIREBASE_DATABASE_URL"
