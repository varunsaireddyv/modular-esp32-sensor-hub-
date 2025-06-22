#include "sdlogger.h"
#include <SD.h>

namespace SdLogger {
    int _csPin;

    void init(int csPin) {
        _csPin = csPin;
        if (!SD.begin(_csPin)) {
            Serial.println("SD card init failed!");
            return;
        }
        Serial.println("SD card ready.");

        if (!SD.exists("/logs.csv")) {
            File file = SD.open("/logs.csv", FILE_WRITE);
            if (file) {
                file.println("Time stamp,MQ135-D,MQ135-A,DHT22,RAIN-A,RAIN-D,SOUND-A,SOUND-D,SOIL-A,SOIL-D,MPU6050,BMP180,BH1750");
                file.close();
            } else {
                Serial.println("Failed to write header to SD.");
            }
        }
    }

    void writeRow(
        String timestamp,
        String MQ135_D, String MQ135_A,
        String DHT22,
        String RAIN_A, String RAIN_D,
        String SOUND_A, String SOUND_D,
        String SOIL_A, String SOIL_D,
        String MPU6050,
        String BMP180,
        String BH1750
    ) {
        File file = SD.open("/logs.csv", FILE_APPEND);
        if (file) {
            file.print(timestamp); file.print(",");
            file.print(MQ135_D); file.print(",");
            file.print(MQ135_A); file.print(",");
            file.print(DHT22); file.print(",");
            file.print(RAIN_A); file.print(",");
            file.print(RAIN_D); file.print(",");
            file.print(SOUND_A); file.print(",");
            file.print(SOUND_D); file.print(",");
            file.print(SOIL_A); file.print(",");
            file.print(SOIL_D); file.print(",");
            file.print(MPU6050); file.print(",");
            file.print(BMP180); file.print(",");
            file.println(BH1750);
            file.close();
        } else {
            Serial.println("Failed to open logs.csv for writing.");
        }
    }
}
