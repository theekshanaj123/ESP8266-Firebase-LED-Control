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
// int intValue;
float floatValue;
bool signupOK = false;
const int LED_PIN = A0;
unsigned long blinkStartTime;         // Store the start time of the blinking
unsigned long blinkDuration = 30000;  // Blink duration in milliseconds
unsigned long ledMillis = 0;
unsigned long blinkInterval = 1000;  // Blink interval in milliseconds
bool databaseUpdated = false;
unsigned long blinkCounter = 0;



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
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  blinkStartTime = millis();  // Initialize the start time

  if (Firebase.ready() && signupOK) {
    Firebase.RTDB.setInt(&fbdo, "/test/int", 1);
    digitalWrite(LED_BUILTIN, HIGH);
  }
}



unsigned long previousMillis = 0;
const long interval = 500;  // Blink interval in milliseconds
int blinkCount = 0;
bool isBlinking = false;
int intValue = 0;  // Initialize
unsigned long startBlinkMillis = 0;

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1500 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/test/int")) {
      if (fbdo.dataType() == "int") {
        intValue = fbdo.intData();
        Serial.println(intValue);
        if (intValue == 0) {
          digitalWrite(LED_BUILTIN, HIGH);  // Turn off the LED
          isBlinking = false;
        } else if (intValue == 1 && !isBlinking) {
          // Start blinking when intValue is 1 and not already blinking
          isBlinking = true;
          blinkCount = 0;
          previousMillis = millis();
          startBlinkMillis = millis();
        } else {
          Serial.println("Invalid value received from Firebase: " + String(intValue));
        }
      } else {
        Serial.println("Unexpected data type received from Firebase.");
      }
    } else {
      Serial.println("Firebase read error: " + fbdo.errorReason());
    }
  }

  // Handle LED blinking
  if (isBlinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // Toggle LED state
      blinkCount++;
      if (blinkCount >= 40) {  // Blink the LED 10 times (20 half-second intervals)
        isBlinking = false;
        digitalWrite(LED_BUILTIN, HIGH);  // Turn off the LED
        // Set Firebase value to 0
        Firebase.RTDB.setInt(&fbdo, "/test/int", 0);
        // Firebase.updateNode(&fbdo, "/test/int", 0);
      }
    }

    // Check if 1 minute has passed
    // if (currentMillis - startBlinkMillis >= 60000) {
    //   isBlinking = false;
    //   digitalWrite(LED_BUILTIN, HIGH);
    //   Firebase.RTDB.setInt(&fbdo, "/test/int", 0);
    //   // Firebase.RTDB.updateNode()updateNode(&fbdo, "/test/int", 0);
    // }
  }
}
