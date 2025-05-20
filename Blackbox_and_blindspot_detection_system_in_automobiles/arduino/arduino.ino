//Arduino20


#include <Wire.h>
#include <MPU6050_tockn.h>
#include <DHT.h>

const int mq3Pin = A2;
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const int maxDistance = 10;
const int sensorPin = A0;  // Pin connected to the vibration sensor
const int threshold = 100; 

#define MPU6050_ADDRESS 0x68 
#define DHTPIN 2     // What digital pin the DHT11 is connected to
#define DHTTYPE DHT11   // DHT 11

MPU6050 mpu6050(Wire, 1.0, 1.0); 
DHT dht(DHTPIN, DHTTYPE);

int16_t gx, gy, gz;


void setup() {
  Serial.begin(115200);
  Serial.println("HANDSHAKE");
  Wire.begin();
  dht.begin();

  // Wake up the MPU6050
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  mpu6050.begin(); 
  mpu6050.calcGyroOffsets(true); 
  Serial.println("‎");

 pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Set up the LED pin
  pinMode(ledPin, OUTPUT);
  
  // Send a handshake message
  
}

void loop() {
  // Read vibration sensor
  int Vb = analogRead(sensorPin); // Read analog value from sensor
  int vi = 0;
  if (Vb > threshold) {
    vi = 1; 
    // Serial.println(vi);
  }
  
  // Read MPU6050 sensor
  mpu6050.update();
  
  gx = mpu6050.getGyroX();
  gy = mpu6050.getGyroY();
  gz = mpu6050.getGyroZ();

  // Tilt warning
  int ti = 0;
  if (gx > 100 || gx < -100 || gy > 100 || gy < -100 || gz > 100 || gz < -100) {
    ti = 1; 
    // Serial.println(ti);
  }

  // Read DHT11 sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Temperature warning
  int wi = 0;
  if (t > 35) {
    wi=1;
    // Serial.println(wi);
  }

  // Read alcohol sensor
  int Al = analogRead(mq3Pin);

  // If alcohol level is above a certain threshold, display warning message
  int ai = 0;
  if (Al > 300) { 
    ai=1;
    // Serial.println(ai);
  }

  // Ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the time it takes for the pulse to return
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;
  
  // If the distance is less than maxDistance, turn on the LED, otherwise turn it off
  if (distance < maxDistance) {
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
  }

  // NodeMCU data transmission
  // Send all sensor data in a single line, separated by '|'
  if (!isnan(h) && !isnan(t)) {
    Serial.print("T = "); Serial.println(t); 
    Serial.print("H = "); Serial.println(h); 
    Serial.print("gx = "); Serial.println(gx); 
    Serial.print("gy = "); Serial.println(gy); 
    Serial.print("gz = "); Serial.println(gz);
    Serial.print("vi = "); Serial.println(vi);   // Vibration alert
    Serial.print("ti = "); Serial.println(ti);  // Tilt alert
    Serial.print("wi = "); Serial.println(wi);   // Temperature alert
    Serial.print("ai = "); Serial.println(ai);  // Alcohol alert
  }
  
  delay(1000); 
}
