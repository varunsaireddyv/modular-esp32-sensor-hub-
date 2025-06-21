#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <MPU6050.h>
#include <Adafruit_BMP085.h>
#include <BH1750.h>

// SensorManager class
class SensorManager {
public:
    void begin();
    void detectConnectedSensors();
    void readAll();
};

// Declare global sensor instances + presence flags
extern MPU6050 mpu;
extern Adafruit_BMP085 bmp;
extern BH1750 lightMeter;

extern bool MQ135a_present;
extern bool MQ135d_present;
extern bool DHT22_present;
extern bool RAINa_present;
extern bool RAINd_present;
extern bool SOUNDa_present;
extern bool SOUNDd_present;
extern bool SOILa_present;
extern bool SOILd_present;

extern bool MPU6050_present;
extern bool BMP180_present;
extern bool BH1750_present;
extern bool OLED_present;

#endif
