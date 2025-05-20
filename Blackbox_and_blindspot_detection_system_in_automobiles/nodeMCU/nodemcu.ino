#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(D2, D3); // RX, TX
TinyGPSPlus gps;

String lastLoc = "";
float lastSpeed = -1;

#define WIFI_SSID "ss"
#define WIFI_PASSWORD "password"
#define API_KEY "apikey"
#define DATABASE_URL "https://data-blackbox-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
int dataCount = 0;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Sign-up OK");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop() {
  float s;
  String loc;
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        loc = String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
      }
      if (gps.speed.isValid()) {
        s = gps.speed.kmph();
    }
      // Only print if the location or speed has changed
      if (loc != lastLoc || s != lastSpeed) {
        if(!loc.equals("") && s != 0){
           Serial.print("loc= ");
           Serial.println(loc);
           Serial.print("s= ");
           Serial.println(s);
           lastLoc = loc;
           lastSpeed = s;
           delay(1000);
          }
        }
  }
 }

  if (Firebase.ready() && signupOK && Serial.available()) {
    String data = Serial.readStringUntil('\n');
    
    int pipeIndex1 = data.indexOf('|');
    int pipeIndex2 = data.indexOf('|', pipeIndex1 + 1);
    int pipeIndex3 = data.indexOf('|', pipeIndex2 + 1);
    int pipeIndex4 = data.indexOf('|', pipeIndex3 + 1);
    int pipeIndex5 = data.indexOf('|', pipeIndex4 + 1);
    int pipeIndex6 = data.indexOf('|', pipeIndex5 + 1);
    int pipeIndex7 = data.indexOf('|', pipeIndex6 + 1);
    int pipeIndex8 = data.indexOf('|', pipeIndex7 + 1);

    if (pipeIndex1 != -1 && pipeIndex2 != -1 && pipeIndex3 != -1 && pipeIndex4 != -1 && pipeIndex5 != -1 && pipeIndex6 != -1 && pipeIndex7 != -1 && pipeIndex8 != -1) {
      float t = data.substring(3, pipeIndex1 - 1).toFloat();
      float h = data.substring(pipeIndex1 + 5, pipeIndex2 - 1).toFloat();
      int gx = data.substring(pipeIndex2 + 10, pipeIndex3 - 1).toInt();
      int gy = data.substring(pipeIndex3 + 10, pipeIndex4 - 1).toInt();
      int gz = data.substring(pipeIndex4 + 10, pipeIndex5 - 1).toInt();
      int vi = data.substring(pipeIndex5 + 10, pipeIndex6 - 1).toInt();
      int ti = data.substring(pipeIndex6 + 10, pipeIndex7 - 1).toInt();
      int wi = data.substring(pipeIndex7 + 10, pipeIndex8 - 1).toInt();
      int ai = data.substring(pipeIndex8 + 10).toInt();
      

      Serial.printf("Received data: T = %.2f, H = %.2f, gx = %d, gy = %d, gz = %d, vi = %d, ti = %d, wi = %d ai = %d\n", t, h, gx, gy, gz, vi, ti, wi, ai);
      
      // Create a FirebaseJson object
      FirebaseJson jsonData;

      // Add all data to the jsonData object
      jsonData.set("T", t);
      jsonData.set("H", h);
      jsonData.set("gx", gx);
      jsonData.set("gy", gy);
      jsonData.set("gz", gz);
      jsonData.set("vi", vi);
      jsonData.set("ti", ti);
      jsonData.set("wi", wi);
      jsonData.set("ai", ai);
      jsonData.set("loc", loc);
      jsonData.set("s", s);

      // Create a data path
      String dataPath = "/data" + String(dataCount);

      // Push the jsonData object to Firebase
      if (Firebase.RTDB.setJSON(&fbdo, dataPath, &jsonData)) {
        Serial.println("Data and location sent to Firebase successfully!");
        Serial.print("Location sent: ");
        Serial.println(loc);
        Serial.print("Speed sent: ");
        Serial.println(s);
        dataCount++;
      } else {
        // Handle the error
        Serial.println("Failed to send data to Firebase");
        Serial.println("Reason: " + String(fbdo.errorReason()));
      }
    }
  }
}
