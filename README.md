# HZ01 Bluetooth Module (ESP32 Bridge)

## Overview
This project implements a **Bluetooth SPP (Serial Port Profile) bridge** using the **ESP32 WROOM‑32E** chipset.  
It forwards data between Bluetooth and UART2, with LED activity feedback. Designed as a lightweight alternative to the HC‑05 module.

---

## Features
- 🔗 Classic Bluetooth SPP communication (`BluetoothSerial`)
- 🔄 Bidirectional UART forwarding (ESP32 ↔ external module)
- 💡 LED activity indicator with non‑blocking blink logic
- 🛠️ Developed and tested on **Arduino IDE 2.3.6**
- 📱 Custom Bluetooth device name: `Audib_BT`

---

## Hardware
- **Board**: ESP32 WROOM‑32E  
- **Pins**:  
  - UART2 RX → GPIO16  
  - UART2 TX → GPIO17  
  - LED → GPIO2  

---

## Installation
1. Install [Arduino IDE 2.3.6](https://www.arduino.cc/en/software).
2. Add ESP32 board support via **Boards Manager**.
3. Clone or download this repository.
4. Open the `.ino` file in Arduino IDE.
5. Select **ESP32 WROOM‑32E** as target board.
6. Upload the sketch to your ESP32.

---

## Usage
- Pair your device with **Audib_BT** (shown in Bluetooth settings).
- Send data via Bluetooth; it will be forwarded to UART2.
- LED blinks on activity.
- Monitor traffic via Arduino Serial Monitor at **115200 baud**.
