
# ESP32 IR Sensor with MQTT and LED Control

**Author:** Anas Mohamed  
**Date:** April 2025  
**Board:** ESP32  
**LinkedIn:** [anas-mohamed-401263287](https://www.linkedin.com/in/anas-mohamed-401263287)

---

## 🔧 Project Description

This project demonstrates the integration of an ESP32 with an IR sensor and LED control using MQTT protocol. It connects to a Wi-Fi network, subscribes to a topic for LED control, and publishes messages based on the IR sensor's object detection status.

---

## 📦 Features

- Connects to Wi-Fi and MQTT broker.
- Publishes IR sensor state to MQTT topic `/test/sector/anas`.
- Subscribes to topic `/test/sector/led` to receive LED ON/OFF commands.
- Handles invalid commands with error feedback (LED blinking).
- Real-time feedback over Serial Monitor.

---

## 🔌 Hardware Requirements

- ESP32 Development Board  
- IR Sensor (Digital output)  
- LED + Resistor  
- Breadboard and jumper wires  
- Wi-Fi access

---

## 🔄 MQTT Topics

| Direction | Topic               | Message Examples         |
|-----------|--------------------|--------------------------|
| Publish   | /test/sector/anas  | "detect object", "not detect object" |
| Subscribe | /test/sector/led   | "turn on", "turn off"    |

---

## 🔐 Wi-Fi & MQTT Configuration

```cpp
const char ssid[] = "anas";              // Your Wi-Fi SSID
const char pass[] = "123456789";         // Your Wi-Fi Password
const char *broker = "broker.emqx.io";   // Public MQTT Broker
const int port = 1883;                   // MQTT Port
```

---

## 🧠 Behavior

- The IR sensor detects obstacles (active LOW).
- If an obstacle is detected, it publishes "detect object".
- If not, it publishes "not detect object".
- MQTT messages like "turn on" or "turn off" will control the LED.
- Any wrong message will blink the LED 5 times as an alert.

---

## ✅ How to Use

1. Upload the code to ESP32 using Arduino IDE or PlatformIO.
2. Make sure your IR sensor is connected to GPIO 5.
3. Connect the LED to GPIO 4 with appropriate resistor.
4. Monitor messages using Serial Monitor (baud 9600).
5. Use MQTT client (e.g., MQTTX, Node-RED, or Python script) to send commands and monitor feedback.

---

## 📬 Contact

Feel free to connect with me on [LinkedIn](https://www.linkedin.com/in/anas-mohamed-401263287).

