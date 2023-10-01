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

## Usage

1. **Power up your ESP8266 board.**

2. The board will create a Wi-Fi access point named "AutoConnectAP." **Connect your computer or mobile device to this access point.**

3. **Open a web browser** and navigate to [http://192.168.4.1](http://192.168.4.1) to access the configuration page.

4. **Follow the on-screen instructions** to connect the ESP8266 to your Wi-Fi network.

5. Once connected, the ESP8266 will connect to Firebase and sign up.

6. You can control the LED by changing the value in the Firebase Realtime Database. **Set the value at `/test/int` to either `0` or `1`** to turn the LED off or on, respectively.

### LED Blinking

The sketch also includes a feature that blinks the LED when the Firebase RTDB value is set to `1`. It blinks the LED 40 times with a half-second interval and then turns the LED off.
