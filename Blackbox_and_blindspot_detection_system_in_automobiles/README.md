# 🚗 Black Box and Blind Spot Detection System in Automobiles

An IoT-powered vehicle safety system that combines a **black box data recorder** and a **real-time blind spot detection** feature. This project uses Arduino, NodeMCU, various sensors, and Firebase integration to enable cloud-based data logging, real-time alerts, and remote vehicle monitoring via a web interface.

---

## 📌 Features

- 🔴 **Crash Detection**: Detects impact and overturning using vibration and tilt sensors.
- 🍷 **Alcohol Detection**: Monitors the presence of alcohol inside the vehicle.
- 🌡️ **Temperature Monitoring**: Detects in-cabin high temperature/humidity.
- 📍 **Location Tracking**: Provides real-time GPS location and speed.
- 🛑 **Blind Spot Detection**: Ultrasonic sensor detects nearby objects and alerts with LED.
- ☁️ **Cloud Integration**: Sends sensor data to Firebase Realtime Database.
- 💻 **Web Interface**: Real-time visualization through a responsive website.

---

## 🛠️ Hardware Components

- **Arduino UNO** – Sensor interface and local processing
- **NodeMCU (ESP8266)** – Wi-Fi & Firebase communication
- **Sensors Used**:
  - Neo 6M GPS Module
  - SW520D Vibration Sensor
  - MQ2 Alcohol/Gas Sensor
  - MPU6050 Accelerometer & Gyroscope
  - DHT11 Temperature & Humidity Sensor
  - HC-SR04 Ultrasonic Sensor (Blind Spot)
- **LED Indicators**
- **Power Supply Modules**

---

## 🧠 Software & Tools

- **Arduino IDE** – Code development and upload
- **Firebase Realtime Database** – Data logging and syncing
- **Firebase Hosting** – Website deployment
- **Node.js + Firebase CLI** – Web deployment and database management
- **HTML, CSS, JavaScript** – Web app development

---

## 🗂️ Repository Structure


---

## ⚙️ System Workflow

1. **Sensor Data Acquisition**:
   - Arduino collects data from multiple sensors.
   - GPS connects directly to NodeMCU.
2. **Data Transmission**:
   - Arduino sends sensor data to NodeMCU via SoftwareSerial.
   - NodeMCU pushes the data to Firebase Realtime Database.
3. **Data Visualization**:
   - Web app (hosted on Firebase) fetches and displays the data in real time.
   - Interface includes vehicle parameters like tilt, temperature, alcohol status, GPS location.
4. **Blind Spot Detection**:
   - Arduino triggers LED alert if an object is detected in the blind spot using ultrasonic sensor.

---

## 🧪 Testing Summary

| Test Case               | Result               |
|------------------------|----------------------|
| Crash Detection        | Successfully detected with SW520D sensor |
| Tilt Measurement       | Detected using MPU6050 during simulated overturn |
| Alcohol Detection      | Triggered alerts with known alcohol samples |
| Temperature Readings   | Accurate DHT11 results under varied conditions |
| GPS Location Tracking  | Real-time updates via Neo 6M and Firebase |
| Blind Spot Alerts      | Successfully triggered LED with nearby objects |

---

## 🌐 Website Overview

A Firebase-hosted web app built with HTML, CSS, and JavaScript.  
The dashboard provides:

- 📈 Live data monitoring
- 🔔 Safety alerts (alcohol, crash, tilt, temperature)
- 🗺️ Real-time GPS coordinates

> 🔗 Link to the hosted website (to be added after deployment)

---

## 🧾 Applications

- Accident Reconstruction & Investigation
- Blind Spot Awareness for Drivers
- Insurance Claim Verification
- Fleet Monitoring and Safety Alerts
- Real-time Vehicle Health & Location Logging

---

## 🚀 Future Improvements

- Integrate LiDAR for precise obstacle detection.
- Add machine learning for crash prediction and anomaly detection.
- Android/iOS companion app.
- Store data logs for retrospective trip analysis.
- Expand to commercial fleet analytics and traffic pattern prediction.

---

## 👨‍💻 Project Contributors

- Vaibhav S (VML20EC051)  
- Aswin Divakaran (VML20EC018)  
- Sreejishnu PA (VML20EC049)  
- Nibin BV (VML20EC038)

**Guide:** Dr. Roshini TV  
**Institution:** Vimal Jyothi Engineering College, APJ Abdul Kalam Technological University

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---


