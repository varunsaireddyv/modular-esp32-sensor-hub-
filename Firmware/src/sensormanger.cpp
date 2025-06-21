#include "sensormanger.h"
#include <Wire.h>
#include "pins.h"

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

    // Analog detection (threshold > 50)
    if (analogRead(MQ135_A1_PIN) > 50)    MQ135a_present = true;   // MQ135 (Gas Sensor) - Analog
    if (analogRead(DHT22_PIN) > 50)       DHT22_present = true;     // DHT22 (Temp + Humidity) - Analog mode read
    if (analogRead(RAIN_A1_PIN) > 50)     RAINa_present = true;     // Rain Sensor - Analog
    if (analogRead(SOUND_A1_PIN) > 50)    SOUNDa_present = true;    // Sound Sensor - Analog
    if (analogRead(SOIL_A1_PIN) > 50)     SOILa_present = true;     // Soil Moisture Sensor - Analog


    // Digital detection (valid HIGH or LOW = sensor likely connected)
    int val;

    val = digitalRead(MQ135_D1_PIN);
    if (val == LOW || val == HIGH) MQ135d_present = true;           // MQ135 (Gas Sensor) - Digital

    val = digitalRead(RAIN_D1_PIN);
    if (val == LOW || val == HIGH) RAINd_present = true;            // Rain Sensor - Digital

    val = digitalRead(SOUND_D1_PIN);
    if (val == LOW || val == HIGH) SOUNDd_present = true;           // Sound Sensor - Digital

    val = digitalRead(SOIL_D1_PIN);
    if (val == LOW || val == HIGH) SOILd_present = true;            // Soil Moisture Sensor - Digital


    // I2C detection (varies based on sensor check library of your sensor)
    Wire.begin();
    
    mpu.initialize();
    if (mpu.testConnection()) {                                     //Gyro+Accel
        MPU6050_present = true;
    }

    if (bmp.begin()) {                                              //Temp+pressure
        BMP180_present = true;
    }

    if (lightMeter.begin()) {                                       //Light
        BH1750_present = true;
    }

    


}

void SensorManager::readAll() {

    // Analog sensors
    if (MQ135a_present) {
        int val = analogRead(MQ135_A1_PIN);
        Serial.print("MQ135_A: "); Serial.println(val);
    } 

    if (DHT22_present) {
        int val = analogRead(DHT22_PIN);
        Serial.print("DHT22_A: "); Serial.println(val);
    } 

    if (RAINa_present) {
        int val = analogRead(RAIN_A1_PIN);
        Serial.print("Rain_A: "); Serial.println(val);
    } 

    if (SOUNDa_present) {
        int val = analogRead(SOUND_A1_PIN);
        Serial.print("Sound_A: "); Serial.println(val);
    }

    if (SOILa_present) {
        int val = analogRead(SOIL_A1_PIN);
        Serial.print("Soil_A: "); Serial.println(val);
    }

    // Digital sensors
    if (MQ135d_present) {
        int val = digitalRead(MQ135_D1_PIN);
        Serial.print("MQ135_D: "); Serial.println(val);
    }

    if (RAINd_present) {
        int val = digitalRead(RAIN_D1_PIN);
        Serial.print("Rain_D: "); Serial.println(val);
    } 

    if (SOUNDd_present) {
        int val = digitalRead(SOUND_D1_PIN);
        Serial.print("Sound_D: "); Serial.println(val);
    } 

    if (SOILd_present) {
        int val = digitalRead(SOIL_D1_PIN);
        Serial.print("Soil_D: "); Serial.println(val);
    }

    //I2C
    if (MPU6050_present) {
        int16_t ax, ay, az;
        int16_t gx, gy, gz;
    
        mpu.getAcceleration(&ax, &ay, &az);
        mpu.getRotation(&gx, &gy, &gz);
    
        Serial.println("MPU6050 Readings:");
        Serial.print("Accel X: "); Serial.print(ax);
        Serial.print(" Y: "); Serial.print(ay);
        Serial.print(" Z: "); Serial.println(az);
    
        Serial.print("Gyro X: "); Serial.print(gx);
        Serial.print(" Y: "); Serial.print(gy);
        Serial.print(" Z: "); Serial.println(gz);
    }
    
    
    
    
    if (BMP180_present) {
        float temp = bmp.readTemperature();
        int pressure = bmp.readPressure();
    
        Serial.print("BMP180 Temp: "); Serial.print(temp); Serial.print(" °C");
        Serial.print(" | Pressure: "); Serial.print(pressure); Serial.println(" Pa");
    }
    
    if (BH1750_present) {
        float lux = lightMeter.readLightLevel();
        Serial.print("BH1750 Light: "); Serial.print(lux); Serial.println(" lx");
    }

}

