# QuakeMesh: Earthquake Early Warning System

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-green.svg)
![Framework](https://img.shields.io/badge/framework-Arduino-blue.svg)

## Overview
**QuakeMesh** is a low-cost, open-source, multi-node earthquake early warning system designed for Indian neighbourhoods, villages and educational campuses. Instead of relying on a single expensive sensor station, QuakeMesh uses a network of affordable ESP32-based nodes that communicate with each other. When one node detects strong ground motion, it immediately alerts nearby nodes, creating a local early-warning mesh.

This project was developed for the **FOSSEE Open Hardware Make-A-Thon 2026** and is validated as a working multiboard prototype on the Velxio simulator.

## Repository Structure
This repository contains the firmware for a dual-node system and the full project documentation.

- \
node1_sender/\: Contains \
node1_sender.ino\ - The sensor node that reads from the MPU6050 accelerometer, calculates magnitude, drives local alerts, and transmits an \ALERT\ signal over Serial/UART upon strong detection.
- \
node2_receiver/\: Contains \
node2_receiver.ino\ - The receiver node that listens for incoming alerts and activates its own buzzer and LED to warn users.
- \docs/\: Contains the full project report in both Markdown (\QuakeMesh_Project_Report.md\) and Word (\QuakeMesh_Project_Report.docx\) formats.

## Hardware Required (per node)
- 1x ESP32 DevKit V1
- 1x MPU6050 (Accelerometer + Gyroscope)
- 1x SSD1306 OLED Display (0.96" I2C)
- 1x Buzzer (Active/Passive)
- 3x LEDs (Red, Yellow, Green)
- 3x 220 O Resistors

## Setup & Testing
1. Clone this repository.
2. Open the \
node1_sender.ino\ and \
node2_receiver.ino\ files in the Arduino IDE.
3. Flash the firmware to two separate ESP32 boards.
4. Wire the components according to the pin mapping in the Project Report.
5. Connect the \TX0\ pin of Node-1 to the \RX0\ pin of Node-2 to establish the serial communication link.
6. **Calibration:** The \TRIGGER_RATIO\ thresholds in Node 1 (\LIGHT = 1.4\, \MEDIUM = 2.4\, \STRONG = 3.3\) are baseline values. Calibrate these based on physical shake-table testing.

## Velxio Project Link
The original simulated prototype can be viewed and tested here:
[Velxio Simulator Project](https://velxio.dev/project/72f37e53-397b-418e-98e0-a470ec03fdcf)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
Hardware concepts are released under the CERN Open Hardware Licence Version 2 (CERN-OHL-W).
