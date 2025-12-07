/*
Device Name:  HZ01 Bluetooth module (ESP32 board as an alternative to the HC‑05 Bluetooth module) 
Release: Light Version
Version: 1.0
Target Chipset: ESP32 WROOM 32E 
IDE: ARDUINO IDE 2.3.6
Developer: Arun.S
Location: INDIA, KERALA, TVM,
E-mail: arunvtkl@gmail.com
Date: 27-11-2025
*/


#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
HardwareSerial MySerial(2);

const int ledPin = 2;
unsigned long lastBlink = 0;
const unsigned long blinkDelay = 300; // ms

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Audib_BT");
  MySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  pinMode(ledPin, OUTPUT);
  Serial.println("ESP32 Bluetooth SPP started. Pair with ESP32_BT.");
}

void loop() {
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();

    // Always forward to UART2
    MySerial.write(incomingChar);

    // Also print to USB Serial Monitor
    Serial.print("Received: ");
    Serial.println(incomingChar);

    // Blink LED only if enough time passed
    unsigned long now = millis();
    if (now - lastBlink > blinkDelay) {
      lastBlink = now;
      digitalWrite(ledPin, HIGH);
      delay(100);
      digitalWrite(ledPin, LOW);
    }
  }
}