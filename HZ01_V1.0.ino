/*
Device Name:  HZ01 Bluetooth module (ESP32 board as an alternative to the HC05 Bluetooth module) 
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

// non-blocking short blink duration
unsigned long ledOnUntil = 0;
const unsigned long ledPulseMs = 100;

const char* btName = "Audib_BT";

void setup() {
  Serial.begin(115200);
  SerialBT.begin(btName); // start SPP with configured device name
  MySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.print("ESP32 Bluetooth SPP started. Pair with ");
  Serial.println(btName);
}

void loop() {
  unsigned long now = millis();

  // Read and forward all available bytes (non-blocking)
  while (SerialBT.available()) {
    int incoming = SerialBT.read();
    if (incoming < 0) break; // nothing to read / error

    uint8_t b = (uint8_t)incoming;
    MySerial.write(b); // forward to UART2

    // Debug printing: printable chars shown as characters, others as hex
    if (isPrintable(b)) {
      Serial.print("Received: ");
      Serial.println((char)b);
    } else {
      // show hex and decimal for clarity
      Serial.print("Received: 0x");
      if (b < 16) Serial.print('0');
      Serial.print(b, HEX);
      Serial.print(" (");
      Serial.print(b);
      Serial.println(")");
    }

    // Blink LED briefly (non-blocking). Only blink if enough time passed since last blink.
    if (now - lastBlink > blinkDelay) {
      lastBlink = now;
      ledOnUntil = now + ledPulseMs;
      digitalWrite(ledPin, HIGH);
    }
    // update now because loop might continue if more bytes are available
    now = millis();
  }

  // Turn off LED when pulse time elapsed
  if (ledOnUntil && millis() > ledOnUntil) {
    digitalWrite(ledPin, LOW);
    ledOnUntil = 0;
  }

  // (optional) small yield to allow WiFi/Bluetooth stack tasks to run
  // yield();
}
