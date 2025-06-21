# modular-esp32-sensor-hub-
Introduction:

This project is a modular ESP32-based sensor hub designed for rapid prototyping and monitoring environements. It supports a wide range of sensors through hot-swappable connectors, with onboard SD card logging, and runs off a 5v li-ion battery. The goal is to offer a deployable, plug-and-play embedded system that’s both scalable and user-friendly.

Primary Design Goals:

Modularity:hot-swappable sensor ports for analog, digital, and I2C devices, swapable power source, programable ESP board

Deployability:standalone and swapable power and onboard storage, light weight custom ESP 32 WROOM 32D board

Plug-and-play:Firmware pre installed and no user input required exept for conecting sensors to premaped sensor pins


---

## Features

- ESP32-WROOM-32D core (Wi-Fi + BLE)
- 13 modular sensor ports: digital, analog, and I2C
- MicroSD card support (SPI) for data logging
- 0.96" OLED screen support via I2C
- Shared I2C bus (GPIO21/GPIO22) with pull-up planning
- Dual voltage rails: 5V (VBUS) and 3.3V (via AMS1117 regulator)
- USB or Li-ion battery input with diode-based auto-switching
- Ground stitched bottom layer with dedicated signal routing on top
- Wide traces (1mm) for power, separate analog and digital zones
- Modular firmware (coming soon)

---

## Pin Mapping

| Function            | GPIO Pin   |
|---------------------|------------|
| I2C SDA             | GPIO21     |
| I2C SCL             | GPIO22     |
| SD Card CS          | GPIO5      |
| SD Card CLK         | GPIO18     |
| SD Card MOSI        | GPIO23     |
| SD Card MISO        | GPIO19     |
| Analog Sensor 1     | GPIO32     |
| Analog Sensor 2     | GPIO33     |
| Digital Sensor 1    | GPIO25     |
| Digital Sensor 2    | GPIO26     |
| Digital Sensor 3    | GPIO27     |
| Digital Sensor 4    | GPIO14     |
| Digital Sensor 5    | GPIO12     |
| Digital Sensor 6    | GPIO13     |
| OLED (I2C)          | Shared     |
| I2C Misc Ports 1-2  | Shared     |

> All analog lines use 1k/2k voltage dividers to drop from 5V to 3.3V safe levels for the ESP32. All sensors are routed through XH-3P connectors with GND, VCC, and Signal/I2C.

---

## Supported Sensors(Default in Firmware)

### Analog / Digital Sensors
- MQ135 (Air Quality)
- DHT22 (Temp & Humidity)
- Raindrop Sensor
- Sound Sensor (x2)
- Soil Moisture
- LDR (Light)
- IR Receiver

### I2C Sensors & Modules
- MPU6050 (Accel + Gyro)
- BME280 (Temp + Pressure + Humidity)
- BH1750 (Light)
- OLED Display


---

## Included Files/Folders

- Schematic: `ESP32_WROOM_D.kicad_sch`
- Board Layout: `PCB_main.kicad_pcb`
- Schematic PNG preview: `Schemtaic.png`
- 3D render: `PCB.png`
- 3D render front: `PCB_F.png`
- 3D render back: `PCB_B.png`
- License: MIT
- Firmware: src/, include/,  lib/, "platform.ini"
- Documents: "ERC", "DRC", "Datasheet", "Pin_mapping"

---

## Firmware flow

1.main.cpp :
-Calls SensorManager.begin() → initializes I2C, sets up pins
-Calls SensorManager.detectConnectedSensors() → auto-detects attached sensors
-Calls SensorManager.readAll() repeatedly inside loop() to read & print sensor data

  
2.sensormanger.cpp/.h :
-Defines bool flags for each supported sensor
-Each sensor has its own analogRead() or I2C detection logic
-readAll() only reads sensors that were marked as detected(bool=true)

  
3.pins.h :
-Central place to edit pin numbers (for future boards or remapping)
-Also includes notes on analog/digital/I2C mappings

---

## Adding own sensors

You can plug in any new sensor to unused analog/digital/I2C ports. Here’s how to support it in firmware:

1. Wiring :
-Connect the sensor to a free port (check Pin Mapping table)
-Use correct GND/VCC/SIG (XH-3P)


2. Modify sensormanger.h :
   
  -Add a flag for presence detection:
      
    extern bool NEW_SENSOR_present;


3. Modify pins.h :
   
  -define your sensor with its GIO pin:
  
    #define NEW_SENSOR_PIN ##   //replace ## with GIO pin(can be found in sensor data sheet)

    
4. Modify sensormanger.cpp :

  -In detectConnectedSensors add:
  
    -if (analogRead(NEW_SENSOR_PIN) > 50) NEW_SENSOR_present = true;   //(for analog sensors)
    -if (analogRead(NEW_SENSOR_PIN) > 50) NEW_SENSOR_present = true;   //(for digital sensors)
    -Check sensor library for I2C (differs from sensor to sensor reffer sesnormanager.cpp for refrence)
   
  -In readAll add:
  
    -if (NEW_SENSOR_present) {
      int val = analogRead(NEW_SENSOR_PIN);   //(for analog)
      }
    -if (NEW_SENSOR_present) {
      int val = digitalRead(NEW_SENSOR_PIN);   //(for analog)
        }
      -Check sensor library for I2C (differs from sensor to sensor reffer sesnormanager.cpp for refrence)

---

## Flashing the Board (PlatformIO)

To upload firmware to the ESP32 board:

1. Install PlatformIO:

   -VSCode + PlatformIO extension
   -Or via CLI: https://platformio.org/install/cli
   
3. Clone this repo:
   
    -git clone https://github.com/varunsaireddyv/modular-esp32-sensor-hub-.git
    -cd modular-esp32-sensor-hub-
   
5. Plug in the board via USB
   
6. Build and upload
    -pio run --target upload

---

## Hardware Design Notes

- 2-layer PCB: Top for signals, Bottom for full GND plane
- GND stitching via multiple vias across zones
- AMS1117 regulator outputs 3.3V rail, with thick trace routing
- Diode-logic used to auto-select between USB or battery power
- All connectors: XH-3P format for modularity
- I2C pull-up resistors placed close to MCU

---

## License

This project is licensed under the MIT License. See `LICENSE` file for full terms.
You may freely modify, distribute, or use this project in your own designs.



