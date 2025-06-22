#ifndef SDLOGGER_H
#define SDLOGGER_H

#include <Arduino.h>

namespace SdLogger {
    void init(int csPin);
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
    );
}

#endif
