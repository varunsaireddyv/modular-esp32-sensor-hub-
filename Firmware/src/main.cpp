#include <Arduino.h>
#include "sensormanger.h"

SensorManager sensors;

void setup() {
  Serial.begin(115200);
  sensors.begin();
  sensors.detectConnectedSensors();
}

void loop() {
  sensors.readAll();
  delay(2000);  
}
