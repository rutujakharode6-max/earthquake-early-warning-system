# Earthquake Early Warning System

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-green.svg)
![Framework](https://img.shields.io/badge/framework-Arduino-blue.svg)

## Overview
This is the single node firmware (MVP) for an Earthquake Early Warning system, developed for the FOSSEE Open Hardware Make-A-Thon 2026. 
It uses an ESP32 microcontroller along with an MPU6050 accelerometer to continuously monitor vibrations and trigger an alert (buzzer and relay) when a sudden spike in vibration energy is detected.

## Hardware Required
- ESP32
- MPU6050 (Accelerometer)
- SSD1306 OLED Display
- Buzzer
- Relay (for demo solenoid/servo)

## Features
1. **Continuous Monitoring:** Reads acceleration from the MPU6050 continuously.
2. **STA/LTA Check:** Runs a simple short-term average vs long-term average check to detect sudden spikes in vibration energy.
3. **Alert Mechanism:** Sounds the buzzer and fires the relay upon detection of a significant spike.
4. **Live Status:** Displays live status on the SSD1306 OLED.

## Directory Structure
- \earthquake-early-warning-system.ino\: Main Arduino firmware file.
- \docs/\: Contains the project report (\QuakeMesh_Project_Report.docx\).

## Setup & Calibration
- Connect the hardware components as per the standard I2C wiring for MPU6050 and SSD1306.
- Open the \.ino\ file in the Arduino IDE or Velxio.
- **IMPORTANT:** The \TRIGGER_RATIO\ in the firmware needs to be calibrated. Start around 3-4 and adjust it based on manual shakes and shake table testing.

## Velxio Project Link
[Velxio Simulator Project](https://velxio.dev/project/72f37e53-397b-418e-98e0-a470ec03fdcf)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
