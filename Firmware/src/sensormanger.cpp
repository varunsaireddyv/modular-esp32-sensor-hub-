#include "sensormanger.h"
#include <Wire.h>
#include "pins.h"
#include "sdlogger.h" // make sure this is included at the top


MPU6050 mpu;
Adafruit_BMP085 bmp;
BH1750 lightMeter;

bool MQ135a_present = false;
bool MQ135d_present = false;
bool DHT22_present = false;
bool RAINa_present = false;
bool RAINd_present = false;
bool SOUNDa_present = false;
bool SOUNDd_present = false;
bool SOILa_present = false;
bool SOILd_present = false;

bool MPU6050_present = false;
bool BMP180_present = false;
bool BH1750_present = false;
bool OLED_present = false;




void SensorManager::begin() {

    // Setup pins
    pinMode(MQ135_D1_PIN, INPUT);
    pinMode(RAIN_D1_PIN, INPUT);
    pinMode(SOUND_D1_PIN, INPUT);
    pinMode(SOIL_D1_PIN, INPUT);


}


void SensorManager::detectConnectedSensors() {

    // Format sensor readings
    String mq135_d = MQ135d_present ? String(digitalRead(MQ135_D1_PIN)) : "NA";
    String mq135_a = MQ135a_present ? String(analogRead(MQ135_A1_PIN)) : "NA";
    String dht22    = DHT22_present  ? String(analogRead(DHT22_PIN)) : "NA";
    String rain_a   = RAINa_present  ? String(analogRead(RAIN_A1_PIN)) : "NA";
    String rain_d   = RAINd_present  ? String(digitalRead(RAIN_D1_PIN)) : "NA";
    String sound_a  = SOUNDa_present ? String(analogRead(SOUND_A1_PIN)) : "NA";
    String sound_d  = SOUNDd_present ? String(digitalRead(SOUND_D1_PIN)) : "NA";
    String soil_a   = SOILa_present  ? String(analogRead(SOIL_A1_PIN)) : "NA";
    String soil_d   = SOILd_present  ? String(digitalRead(SOIL_D1_PIN)) : "NA";

    // MPU6050 (show only Accel X )
    String mpu6050 = "NA";
    if (MPU6050_present) {
        int16_t ax, ay, az;
        mpu.getAcceleration(&ax, &ay, &az);
        mpu6050 = "AX:" + String(ax) + ",AY:" + String(ay) + ",AZ:" + String(az);
    }

    // BMP180
    String bmp180 = "NA";
    if (BMP180_present) {
        float temp = bmp.readTemperature();
        int pressure = bmp.readPressure();
        bmp180 = String(temp, 1) + "C " + String(pressure) + "Pa";
    }

    // BH1750
    String bh1750 = BH1750_present ? String(lightMeter.readLightLevel(), 1) + "lx" : "NA";

    // FINAL WRITE
    SdLogger::writeRow(
        timestamp,
        mq135_d, mq135_a,
        dht22,
        rain_a, rain_d,
        sound_a, sound_d,
        soil_a, soil_d,
        mpu6050,
        bmp180,
        bh1750
    );


}

