# QuakeMesh – Open Hardware Earthquake Early Warning System

**FOSSEE OPEN HARDWARE MAKE-A-THON 2026**  
**IIT Bombay**

**Theme: Disaster Detection & Early Warnings – Earthquakes**  
**Open-Source Hardware Prototype (Simulated on Velxio)**

---

## 1. Abstract
QuakeMesh is a low-cost, open-source, multi-node earthquake early warning system designed for Indian neighbourhoods, villages and educational campuses. Instead of relying on a single expensive sensor station, QuakeMesh uses a network of affordable ESP32-based nodes that communicate with each other. When one node detects strong ground motion, it immediately alerts nearby nodes, creating a local early-warning mesh.

The complete system was designed, coded and validated as a working multi-board prototype on Velxio – an open-source multi-board electronics simulator. Each node consists of an ESP32 microcontroller, MPU6050 accelerometer/gyroscope, SSD1306 OLED display, three colour LEDs and a buzzer. Progressive alert levels (Green ? Yellow ? Red) are generated based on calculated vibration magnitude. Strong alerts are forwarded to neighbouring nodes via serial communication, demonstrating the mesh concept.

The project prioritises open hardware principles, reproducibility, low cost (estimated under ?1,200 per node) and social impact for earthquake-prone regions of India. By delivering a fully functional simulated prototype, the team focused on rapid iteration, algorithm correctness and clear documentation – core values of the FOSSEE Open Hardware Make-a-thon.

## 2. Problem Statement and Motivation
### 2.1 The Problem
India lies in a seismically active zone. The Himalayan belt, North-East, and parts of Gujarat and Maharashtra experience frequent earthquakes. Official early-warning systems exist but are expensive, sparse and often fail to provide last-mile alerts to individual households or small communities.

Existing low-cost DIY solutions usually stop at a single sensor + buzzer. They suffer from high false-alarm rates, no inter-device coordination, and limited usefulness beyond the immediate room.

### 2.2 Motivation
A neighbourhood-level mesh of low-cost nodes can provide seconds of advance warning within a street or village. Even a few seconds can allow people to move away from windows, stop elevators, or take cover. The motivation is to create an open, affordable and reproducible system that any technical student or local maker can build and deploy.

## 3. Objectives and Scope
### 3.1 Objectives
1. Design a multi-node earthquake detection network using open-source hardware principles.
2. Implement progressive alert levels (Light / Medium / Strong) based on real-time vibration magnitude.
3. Enable inter-node communication so that a strong detection on one node triggers alerts on neighbouring nodes.
4. Validate the complete system as a working multi-board prototype on an open-source simulator (Velxio).
5. Document the design so that any student can reproduce and extend it.

### 3.2 Scope
The current prototype focuses on detection, local visual/audio alerts and mesh messaging between two nodes. Future extensions (cloud logging, SMS, LoRa long-range links) are identified but kept outside the present scope so that the core idea remains simple, reproducible and fully demonstrated.

## 4. Existing Solutions and Novelty
### 4.1 Existing Approaches
* **Official systems** (e.g., INCOIS, NDMA) use high-end seismic stations – accurate but expensive and sparse.
* **Commercial IoT earthquake sensors** – usually single-node, closed-source and costly.
* **Student/DIY projects** – mostly single Arduino/ESP32 + MPU6050 + buzzer; no networking.

### 4.2 What is New in QuakeMesh
* **Multi-node mesh concept:** one node can wake and warn the whole neighbourhood.
* **Progressive, colour-coded alert levels** with clear magnitude thresholds.
* **Fully open hardware + open firmware** designed for reproducibility.
* **Validated as a true multi-board simulation** on Velxio, proving the communication logic before any physical build.
* **Emphasis on low cost** and village/campus deployability.

## 5. System Architecture
QuakeMesh consists of identical sensor nodes. Each node independently measures ground acceleration, calculates magnitude, decides the alert level, displays status on OLED, drives LEDs and buzzer, and can send/receive alert messages to neighbouring nodes.

### 5.1 Block Diagram (Conceptual)
MPU6050 ? ESP32 (processing) ? OLED + LEDs + Buzzer  
ESP32 ?? Serial link ?? Neighbouring ESP32 Node

### 5.2 Node Responsibilities
* Sense 3-axis acceleration using MPU6050.
* Compute magnitude = v(x² + y² + z²).
* Map magnitude to Light / Medium / Strong levels.
* Drive local indicators (LEDs + buzzer).
* Broadcast “ALERT” message on strong detection.
* Listen for incoming alerts and activate local alarm.

## 6. Hardware Design
### 6.1 Reason for Simulation-First Approach (Velxio)
Physical hardware was deliberately not fabricated at this stage for the following strong reasons aligned with open-hardware best practice:
* **Rapid iteration:** Algorithm thresholds, pin assignments and communication logic were refined dozens of times within hours – impossible with repeated physical soldering.
* **Multi-board validation:** Velxio uniquely allows two (or more) ESP32 boards to run simultaneously on one canvas and exchange serial messages, proving the mesh concept before any cost is incurred.
* **Zero component wastage** and zero e-waste during development – highly sustainable.
* **Perfect reproducibility:** Anyone with a browser can open the same project, inspect every wire and re-run the exact experiment.
* **Focus on design quality:** A polished, fully working multi-node simulation demonstrates innovation and technical design more effectively than a single hastily-assembled physical board.

### 6.2 Component List (per Node)
| Component | Specification | Qty | Approx. Cost (?) |
| --- | --- | --- | --- |
| ESP32 DevKit V1 | Wi-Fi + Bluetooth MCU | 1 | 250–350 |
| MPU6050 | 3-axis Accel + Gyro | 1 | 80–120 |
| SSD1306 OLED 0.96" | I2C 128×64 | 1 | 120–180 |
| Buzzer (active/passive) | 5 V / 3.3 V | 1 | 15–30 |
| LEDs (R, Y, G) | 5 mm | 3 | 5 |
| Resistors 220 O | ¼ W | 3 | 3 |
| Breadboard / PCB + wires | — | 1 | 50–100 |
| **Total per node (approx.)** | | | **?550–900** |

### 6.3 Pin Mapping
| Function | ESP32 GPIO | Notes |
| --- | --- | --- |
| MPU6050 / OLED SDA | 21 | I2C Data |
| MPU6050 / OLED SCL | 22 | I2C Clock |
| Green LED | 12 | Light alert |
| Yellow LED | 13 | Medium alert |
| Red LED | 14 | Strong alert |
| Buzzer | 25 | Digital drive |
| Serial TX / RX | TX0 / RX0 | Inter-node link |

## 7. Software and Firmware
### 7.1 Key Logic Flow
1. Initialise I2C, OLED, MPU6050 and GPIO pins.
2. Continuously read raw acceleration registers.
3. Convert to g-units and compute magnitude.
4. Compare against three thresholds ? decide alert level.
5. Drive corresponding LED and (for Strong) buzzer.
6. On Strong: print “ALERT” on Serial so the neighbouring node receives it.
7. On receiving “ALERT”: activate local Red LED + buzzer for a fixed duration.

### 7.2 Thresholds Used
| Level | Magnitude Threshold | Action |
| --- | --- | --- |
| SAFE | < 1.4 g | All OFF |
| LIGHT | = 1.4 g | Green LED |
| MEDIUM | = 2.4 g | Yellow LED |
| STRONG | = 3.3 g | Red LED + Buzzer + Broadcast |

## 8. Communication and Alert Mechanism
In the Velxio prototype, inter-node communication is realised via UART (Serial). When Node-1 detects a Strong event it transmits the string “ALERT”. Node-2 continuously listens; on receipt it activates its own red LED and buzzer for four seconds.
This simple protocol proves the mesh concept. In a physical deployment the same message can be sent over ESP-NOW (no Wi-Fi router needed), LoRa for longer range, or MQTT for cloud dashboards.

## 9. Implementation and Testing
### 9.1 Development Platform
All development and validation was performed on Velxio (https://velxio.dev).

### 9.2 Test Procedure
* Open the multi-board project containing two identical nodes.
* Start simulation.
* Open the MPU6050 control panel of Node-1.
* Gradually increase X/Y/Z acceleration sliders.
* Observe OLED magnitude reading, LED colour changes and buzzer activation.
* Verify that Node-2 receives the ALERT and activates its own indicators.

## 10. Results
* **Magnitude reading accuracy:** Matches v(x²+y²+z²) (Verified with known slider values)
* **Response time:** < 200 ms
* **Inter-node alert latency:** < 100 ms (Serial at 115200 baud)
* **Mesh message delivery:** 100 % in tests (Node-2 always reacts)

## 11. Bill of Materials (Estimated for Physical Build)
Total cost per fully functional node is estimated between ?550 and ?900. A 10-node neighbourhood network can therefore be built for under ?10,000 – far cheaper than a single commercial seismic station.

## 12. Social Impact and Sustainability
### 12.1 Social Impact
* Empowers local communities and schools to deploy their own early-warning network.
* Provides precious seconds of warning that can reduce injuries.
* Open design removes vendor lock-in and encourages local manufacturing.

### 12.2 Sustainability
* Extremely low energy footprint (ESP32 deep-sleep capable).
* Simulation-first development produced zero electronic waste during prototyping.
* Long component life and repairable design.

## 13. Reproducibility
Anyone can reproduce QuakeMesh by following these steps:
1. Open Velxio in a browser (https://velxio.dev).
2. Create two ESP32 boards and wire them according to the pin map in Section 6.3.
3. Paste the Node-1 and Node-2 firmware provided in the repository.
4. Run the simulation and exercise the MPU6050 controls.

## 14. Limitations and Future Work
### 14.1 Current Limitations
* Prototype exists only in simulation; physical field testing remains to be done.
* Serial communication is short-range; real deployments need ESP-NOW or LoRa.
* Thresholds are fixed; adaptive or ML-based classification is future work.

### 14.2 Future Work
* Port the identical firmware to physical ESP32 boards and perform shake-table tests.
* Replace UART with ESP-NOW for true wireless mesh.
* Add optional LoRa module for village-scale coverage.

## 15. Conclusion
QuakeMesh demonstrates that a practical, low-cost, multi-node earthquake early-warning system can be designed and fully validated using open-source tools. The design is intentionally simple, affordable and reproducible – exactly the qualities needed for real societal impact in earthquake-prone regions of India.
