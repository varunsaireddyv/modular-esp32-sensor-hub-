#include <Arduino.h>
#include "sensormanger.h"

SensorManager sensors;

void setup() {
  Serial.begin(115200);
  sensors.begin();
}

void loop() {
  sensors.readAll();
  delay(1000);
}
