/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/



#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <WiFiManager.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
// #define WIFI_SSID "Dialog 4G 929"
// #define WIFI_PASSWORD "60c302f3"

// Insert Firebase project API Key
#define API_KEY "AIzaSyAlPBreNK8nZPvmJWDUlB8i9FbBzSqyCtk"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://b-adb-me-default-rtdb.asia-southeast1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int intValue;
float floatValue;
bool signupOK = false;
const int LED_PIN = A0;

void setup() {

  //input and outputs
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  // Create an instance of WiFiManager
  WiFiManager wifiManager;

   // Connect to Wi-Fi or enter configuration mode
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("Failed to connect or configure. Restarting...");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  // Successfully connected or configured
  Serial.println("Connected to Wi-Fi!");

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/test/int")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);

        if(intValue != 1)
        {
          Serial.println("intValue");
          digitalWrite(LED_BUILTIN, HIGH);
        }
        else{
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }

  Serial.println("other on");

}