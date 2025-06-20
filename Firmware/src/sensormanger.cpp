#include "sensormanger.h"
#include <Wire.h>

// Example GPIOs to monitor
#define ANALOG_1_PIN 32
#define ANALOG_2_PIN 33
#define DIGITAL_1_PIN 25
#define DIGITAL_2_PIN 26

void SensorManager::begin() {
    Serial.println("[SensorManager] Starting...");

    // Init I2C bus
    Wire.begin();
    Serial.println("I2C initialized");

    // Setup pins (if needed)
    pinMode(DIGITAL_1_PIN, INPUT);
    pinMode(DIGITAL_2_PIN, INPUT);

}

void SensorManager::readAll() {
    // Analog Reads
    int analog1 = analogRead(ANALOG_1_PIN);
    int analog2 = analogRead(ANALOG_2_PIN);

    // Digital Reads
    int digital1 = digitalRead(DIGITAL_1_PIN);
    int digital2 = digitalRead(DIGITAL_2_PIN);

    // Print status to serial
    Serial.print("Analog1: "); Serial.print(analog1);
    Serial.print(" | Analog2: "); Serial.print(analog2);
    Serial.print(" || Digital1: "); Serial.print(digital1);
    Serial.print(" | Digital2: "); Serial.println(digital2);
}
