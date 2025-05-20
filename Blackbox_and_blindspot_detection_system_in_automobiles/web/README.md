# 🌐 BLACKBOX Vehicle Monitoring Dashboard

This is the web interface of the **Black Box and Blind Spot Detection System in Automobiles** project. It enables real-time monitoring of critical vehicle data such as speed, location, alcohol presence, temperature, tilt, and crash alerts — all collected from Arduino and NodeMCU and synced with Firebase Realtime Database.

---

## 🚀 Key Features

- 📡 Live sensor data updates from Firebase
- 🌍 Clickable Google Maps links for real-time GPS location
- 🌡️ Temperature unit toggle (°C ↔ °F)
- 🚗 Speed unit toggle (m/s ↔ km/h)
- ⚠️ Dynamic alerts:
  - Alcohol detection
  - Crash detection
  - Tilt warning
  - High temperature warning
  - Overspeed alert
- 🖼️ Engaging welcome screen with background image
- 📱 Responsive UI with a modern, clean design
- ☁️ Hosted on Firebase Hosting

---

## 🛠️ Tech Stack

- **Frontend**: HTML, CSS, JavaScript, jQuery
- **Backend/Database**: Firebase Realtime Database
- **Hosting**: Firebase Hosting

---

## 🔧 Firebase Setup Instructions

To run this web dashboard using your own Firebase instance:

1. Go to [Firebase Console](https://console.firebase.google.com/) and create a new project.
2. Enable **Realtime Database** and set up rules if needed.
3. Enable **Firebase Hosting**.
4. Replace the Firebase config in `app.js` with your own:

```js
var firebaseConfig = {
  apiKey: "YOUR_API_KEY",
  authDomain: "YOUR_PROJECT.firebaseapp.com",
  databaseURL: "https://YOUR_PROJECT.firebaseio.com",
  projectId: "YOUR_PROJECT_ID",
  storageBucket: "YOUR_PROJECT.appspot.com",
  messagingSenderId: "YOUR_SENDER_ID",
  appId: "YOUR_APP_ID"
};

