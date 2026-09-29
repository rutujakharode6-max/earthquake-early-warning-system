# REPORT FILE
**TITLE:** Earthquake Detection and Early Warning Alert System
**PROJECT NAME:** QUAKEMESH

**TEAM MEMBERS:**
RUTUJA KHARODE
AMIT SINGH
TAVISHI UMRAO
ANANT PANDEY
SANSKRITI

**INSTITUTION NAME:** VIT BHOPAL UNIVERSITY

---

## 1. Abstract
QuakeMesh is a low-cost, open-source, multi-node earthquake early warning system designed for Indian neighbourhoods, villages and educational campuses. Instead of depending on a single expensive seismic station, the system employs a network of affordable ESP32-based sensor nodes that communicate with one another. When any node detects strong ground motion, it promptly alerts neighbouring nodes, thereby forming a local early-warning mesh.

The complete system has been designed, programmed, and validated as a fully functional multi-board prototype on Velxio, an open-source multi-board electronics simulator. Each node comprises an ESP32 microcontroller, an MPU6050 accelerometer, an SSD1306 OLED display, three coloured LEDs and a buzzer. Progressive alert levels: (Green ? Yellow ? Red) are generated based on the calculated vibration magnitude. Strong alerts are transmitted to adjacent nodes through serial communication, successfully demonstrating the mesh-warning concept.

The project emphasizes open-hardware principles, reproducibility, low cost and potential social impact in earthquake-prone regions of India. By delivering a complete simulated prototype, the work prioritizes rapid iteration, algorithmic correctness, and clear documentation.

## 2. Problem Statement and Motivation
### 2.1 The Problem
A household may not have a dedicated device that senses strong ground motion and provides an immediate local alarm. Many small do-it-yourself projects use a sensor connected to a buzzer, but a single unit cannot notify a separate building unless a communication link is added. Also, that conventional project was not so accurate and sometimes failed to generate alert. A networked approach could make a warning available at more than one location.

The core practical problem addressed by QuakeMesh is: how a low-cost sensor node can detect a configurable level of ground shaking and transmit a clear alert to another node, while remaining fully transparent and reproducible by students?

### 2.2 Motivation
The motivation is educational and social. A locally audible and visible warning may help people become aware of shaking, while a networked design illustrates how neighbouring devices can share information. The project does not claim that a low-cost accelerometer can predict an earthquake before it begins, nor that the prototype provides guaranteed seconds of advance warning. It detects motion at the sensor and relays a message after the threshold is crossed.

## 3. Objectives and Scopes
The main objective is to:-
1. Design the a two-node earthquake-motion alert prototype using an MPU6050
2. Calculate a simple acceleration magnitude; classify readings into progressive alert levels Activate LEDs, a buzzer and an OLED display
3. Transmit a alert message from one node to another
4. Document the design so another student can reproduce the simulation easily just by studying the prototype.

The present scope includes a 
1. two-board simulation, 
2. threshold-based decision logic, 
3. local visual and audio indicators,
4. UART serial messaging. 

It does not include a physical unit, long-range wireless deployment, cloud dashboard, mobile application, professional seismic validation. The current prototype focuses on detection, local visual/audio alerts and mesh messaging between two nodes. Future extensions (cloud logging, SMS, LoRa long-range links) are identified but kept outside the present scope so that the core idea remains simple, reproducible and fully demonstrated.

## 4. Existing Approaches
### 4.1 Existing Approaches
* Official earthquake monitoring is mainly handled by specialized seismic networks and government agencies. These systems use high-quality instrumented stations along with established methods for processing data and sending public warnings.
* Commercial earthquake sensors and IoT-based products are also available in the market, but they are often expensive and closed-sourced.
* Most student and academic projects typically demonstrate a single microcontroller connected to a motion sensor and a local alarm (LED or buzzer). These prototypes work well for basic detection but usually operate in isolation.
* The main gap identified is the lack of coordination between nodes in most basic student prototypes. Almost all of them remain single-node systems

### 4.2 Novelty
* Multi-node mesh alerting: When one node detects strong shaking, it immediately sends an alert to neighbouring nodes. This allows one node to warn others even before they fully sense the earthquake themselves.
* Clear progressive indication: The system uses three simple alert levels - Green, Yellow and Red - based on vibration strength, making it easy for anyone to understand the situation immediately.
* Low-cost and reproducible design: Each node is built using common components (ESP32, MPU6050, OLED, LEDs and buzzer) and costs under (?1,200), making it affordable for students, schools and local communities.
* Simulation-first approach: The complete multi-node system was designed and tested on Velxio, an open-source simulator. This made it possible to properly test communication between nodes and refine the logic quickly without building physical hardware.

## 5. System Architecture
Each node contains a sensing unit, a controller, an output unit, and a communication interface. The MPU6050 provides raw acceleration readings on the X, Y, and Z axes over I2C. The ESP32 reads the values, converts them to approximate g-units, calculates the magnitude, and compares it with configured thresholds. The OLED presents the measured magnitude and current state. LEDs indicate the alert level, and the buzzer provides an audible strong-alert indication.

In the two-node simulation, Node 1 acts as the detecting and transmitting node. When its calculated magnitude exceeds the strong threshold, it prints “ALERT” over serial. Node 2 listens for a complete line when the message equals “ALERT”; it turns on its red LED and buzzer and displays an alert-received message. 

### 5.1. Block Diagram
(Block diagram included in PDF)

For a physical network, the UART link would need to be replaced or bridged by a suitable radio or network protocol. A wireless implementation would also need node identification, message integrity checks, duplicate suppression, timeout handling, and a defined network topology.

## 6. Hardware Design
The design uses commonly available modules so that the circuit can be assembled on a breadboard before a custom PCB is considered. The ESP32 provides processing and serial interfaces. The MPU6050 is connected over I2C; the OLED shares the I2C bus. Three LEDs provide distinct visual states, each with a current-limiting resistor. The buzzer is driven from a digital output, subject to the current limits of the selected device and ESP32 pin.

The pin map below follows the supplied firmware and report. It should be checked against the exact ESP32 development board and module before physical wiring. In particular, GPIO12 can affect ESP32 boot strapping on some boards, and a buzzer that draws more current than a GPIO can safely supply should be driven through a transistor or suitable driver stage.

For an initial physical build, mount the ESP32, sensor and OLED firmly so that the sensor's orientation is known and repeatable. Avoid placing the sensor on a loose or flexible surface. A small enclosure may include openings for the OLED and buzzer, secure mounting points, and access for USB programming. Enclosure drawings and a PCB layout are not included in the supplied source material; these remain design tasks for a physical revision.

### 6.1. Reason for simulation only approach
1. Rapid iteration: Algorithm thresholds, pin assignments and communication logic were refined dozens of times within hours impossible with repeated physical soldering.
2. Multi-board validation: Velxio uniquely allows two (or more) ESP32 boards to run simultaneously on one canvas and exchange serial messages, proving the mesh concept before any cost is incurred.
3. Zero component wastage and zero e-waste during development - highly sustainable.
4. Perfect reproducibility: Anyone with a browser can open the same project, inspect every wire and re-run the exact experiment.
5. Focus on design quality: A polished, fully working multi-node simulation demonstrates these criteria more effectively than a single hastily-assembled physical board.

### 6.2. Components
| Component | Specification / notes | Qty/node |
| --- | --- | --- |
| ESP32 DevKit V1 | Wi-Fi/Bluetooth MCU board | 1 |
| MPU6050 | 3-axis accelerometer + gyroscope | 1 |
| SSD1306 OLED | 0.96-inch, 128×64, I2C | 1 |
| Buzzer | Active/passive, compatible drive | 1 |
| LEDs | Green, yellow and red, 5 mm | 3 |
| Resistors | 220 O, ¼ W current limiting | 3 |
| Breadboard / PCB and wires | Prototype interconnects | 1 set |

### 6.3. Pin Mapping
| Function | Nodes |
| --- | --- |
| MPU6050 / OLED SDA - 21 | I2C Data |
| MPU6050 / OLED SCL - 22 | I2C Clock |
| Green LED - 12 | Light alert |
| Yellow LED - 13 | Medium alert |
| Red LED - 14 | Strong alert |
| Buzzer - 25 | Digital drive |
| Serial TX / RX - TX0 / RX0 | Inter-node link |

### 6.4. PCB Design
(PCB design included in PDF)

## 7. Software and Firmware
The firmware is written for the Arduino framework on ESP32. Node 1 initialises serial communication, output pins, the MPU6050 and the SSD1306 OLED. It wakes the MPU6050 by writing to its power-management register, then repeatedly reads the six acceleration data bytes beginning at register 0x3B. The raw signed readings are divided by 16384.0, corresponding to the MPU6050 nominal sensitivity at the ±2 g setting. The code calculates the vector magnitude as sqrt(x*x + y*y + z*z). It then turns off the indicators before applying the current threshold logic, updates the OLED and waits before the next cycle.

Node 2 initialises its outputs, display and serial interface. It checks whether serial data is available, reads through the newline, trims whitespace and compares the result with “ALERT”. When a match is received, the node activates the red LED and buzzer, updates the OLED, holds the alarm for four seconds, and then switches the red LED and buzzer off.

### 7.1. Threshold logic
The supplied code uses three configurable values: LIGHT = 1.4, MEDIUM = 2.4 and STRONG = 3.3. A magnitude above STRONG activates the red LED and buzzer and transmits the alert. A magnitude above MEDIUM but not above STRONG activates yellow. A magnitude above LIGHT but not above MEDIUM activates green. Otherwise the display reports SAFE and the outputs remain off.

| Threshold Used | Output |
| --- | --- |
| SAFE : < 1.4 g | All OFF |
| LIGHT : = 1.4 g | Green LED |
| MEDIUM : = 2.4 g | Yellow LED |
| STRONG : = 3.3 g | Red LED + Buzzer + Broadcase |

### 7.2. Machine Learning
No machine-learning or TinyML model is used in the current firmware. The decision is deterministic threshold logic, which is straightforward to inspect and reproduce. A future model could be trained to distinguish vibration patterns, but that would require a labelled dataset collected from a range of sensor mountings and real-world disturbances. A model should not be described as reducing false alarms until it has been evaluated against held-out data and documented test conditions.

### 7.3. Flowchart
(Flowchart included in PDF)

## 8. Communication and Alert System
Node 1 transmits the plain-text line “ALERT” through UART at 115200 baud. Node 2 reads the line and reacts only when the trimmed message matches the expected word. The implementation demonstrates the end-to-end software behaviour, but the short serial link is not suitable for separated houses without additional communication hardware.

ESP-NOW is a possible option for short-range device-to-device communication using ESP32 radios. LoRa could be explored where longer range and low data rate are priorities, although coverage depends on antenna, environment, regional radio rules and module settings. GSM or cellular messaging could provide wider-area notifications where service is available. These options require additional firmware, hardware and field tests and are not part of the current demonstrated build.

A more robust message should include a sender ID, sequence number, event time or counter, and a checksum or integrity mechanism. Receivers should ignore repeated messages, record message age and use a defined alarm-reset policy. A multi-hop mesh would need routing and acknowledgement behaviour; simply forwarding a word over one serial connection does not yet implement a full wireless mesh network.

## 9. Implementation and Testing 
Development and functional validation were performed in the Velxio multi-board simulator, according to the supplied project report. Two ESP32 instances were used to represent the detecting node and receiving node. The sensor controls were adjusted to change the simulated acceleration values, and the display, LED and buzzer behaviour was observed.

The documented test sequence is: open the two-board project; start the simulation; adjust the MPU6050 X, Y and Z controls on Node 1; observe the magnitude and progressive indicator changes; cross the strong threshold; and confirm that Node 2 receives the ALERT message and activates its red LED and buzzer.

### 9.1. Image of prototype
(Image of prototype included in PDF)

### 9.2. Calibration and Test Setup
The source firmware assumes the MPU6050 ±2 g range, for which the nominal scale factor is 16384 least-significant bits per g. Before physical testing, confirm the sensor range configuration and compare the stationary readings on all axes with the expected gravity vector for the sensor's orientation. Record offset values and repeat the check after mounting the sensor in its enclosure.

* A physical test setup should use a controlled vibration source or shake table, a rigid sensor mount and a reference instrument if available.
* Test several amplitudes and frequencies, repeat each test, and include non-earthquake disturbances such as walking, door slams and nearby traffic.
* Record raw samples, calculated magnitude, alert state, time from stimulus to local alarm, time to remote alarm and any missed or false alerts.
* Do not perform hazardous tests or represent a simple shake-table test as seismic certification.

## 10. Result
The table below reproduces the functional results reported in the supplied project report. These are reported simulation observations, not independently verified physical measurements.

| Metric | Value stated in source report | Interpretation |
| --- | --- | --- |
| Magnitude calculation | Matches v(x²+y²+z²) | Checked against known simulator slider values |
| Detection to LED | < 200 ms | Source report associates this with 150–200 ms loop delay |
| Inter-node alert latency | < 100 ms | Reported for UART at 115200 baud in simulation |
| False alarms | None under ambient simulation conditions | Not a physical false-alarm rate |
| Progressive alert logic | Correct Green ? Yellow ? Red | Functional simulation observation |
| Message delivery | 100% in reported tests | Node 2 reportedly reacted in each test; test count not specified |

## 11. Bills of Material
For a physical node, the supplied report estimates a total of ?550–?900, depending on local prices. A two-node build would therefore be approximately ?1,100–?1,800 before any wireless modules, enclosure, power supply, shipping or test equipment. These figures are estimates and should be refreshed with supplier quotations before procurement.

## 12. Social Impact and Sustainability
1. A low-cost, repairable educational design can help students and community groups learn about sensing, embedded systems and emergency communication.
2. local makers to inspect, adapt and repair a prototype rather than depending entirely on a proprietary product.
3. The simulation-first approach avoids consuming electronic components during early software iteration. 
4. For a physical version, sustainability would be improved by using replaceable modules, documenting pinouts, avoiding unnecessary disposable parts and designing the enclosure for repair.
5. Any community deployment must include clear user education, reliable power, routine checks and coordination with official disaster-management guidance.
6. QuakeMesh should supplement, not replace, official earthquake alerts, evacuation guidance, building safety measures or emergency services. False alarms and missed detections are possible with the present threshold method.

## 13. Reproducibility and Built Guide
To reproduce the current demonstration, open the Velxio simulator at https://velxio.dev, create two ESP32 boards, add the MPU6050 and SSD1306 display to Node 1, and add the output devices and display to Node 2 as required by the firmware. Wire I2C to GPIO21 (SDA) and GPIO22 (SCL), connect LEDs to GPIO12, GPIO13 and GPIO14 through resistors, and connect the buzzer control to GPIO25.

Load the Node 1 and Node 2 source code from the accompanying firmware file into the corresponding boards. Configure the serial connection at 115200 baud and ensure that the transmitted newline is delivered to the receiver.

GITHUB repository:-
Velxio simulation link:- https://velxio.dev/project/72f37e53-397b-418e-98e0-a470ec03fdcf

## 14. Limitations and Future Work
The present version is simulation-only and has not been evaluated in a physical field deployment. UART communication demonstrates message handling but does not provide wireless neighbourhood coverage. The fixed thresholds have not been validated against a representative dataset, and the magnitude calculation does not currently remove gravity or filter transient noise. There is no cloud dashboard, phone notification, secure message authentication or automatic health monitoring.

The next development stage should build and calibrate physical nodes, verify the sensor's configured range, add signal filtering and event-window logic, and conduct repeatable tests using a controlled vibration source. The serial link can then be replaced with ESP-NOW or a suitable LoRa design. Further work may include node IDs, acknowledgements, message expiry, battery monitoring, event logging and a dashboard.

TinyML could be evaluated only after collecting and labelling representative signals and defining measurable acceptance criteria. The system should be tested for missed alerts, false alarms, response time, range and behaviour during power or communication failures. Any public-facing deployment would require expert review and should not be advertised as a certified warning system without appropriate validation and approval.

## 15. Conclusion
QuakeMesh demonstrates a simple way to connect motion sensing, local alarms and neighbour-to-neighbour alert messaging in one educational project. The ESP32 reads acceleration data from the MPU6050, calculates a magnitude, selects a colour-coded alert level and activates the appropriate outputs. In the two-node simulator, a strong event at Node 1 sends an ALERT message that causes Node 2 to sound its alarm.

The most important outcome is the demonstration of the complete concept in simulation and the documentation of a path toward a physical implementation. The current system is not a substitute for official earthquake warning services and does not yet establish field accuracy, coverage or guaranteed warning time. Physical calibration, robust wireless communication and systematic testing are the necessary next steps.

## 16. Reference
1. MPU-6050 Product Specification and Register Map, InvenSense / TDK. Consult the datasheet for accelerometer range, sensitivity and register details.
2. Espress if Systems, ESP32 Series Datasheet and Technical Reference Manual.
3. Velxio simulator: https://velxio.dev (development platform cited in the supplied project report).
4. National Disaster Management Authority (NDMA), Government of India, earthquake preparedness and safety guidance: https://ndma.gov.in/
5. India Meteorological Department (IMD), earthquake information and seismology resources: https://mausam.imd.gov.in/

## 17. License
1. Firmware / Source Code: Released under the MIT License.
2. Hardware design files, schematics, documentation and this report: Released under the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0) License.

## 18. Acknowledgement
We would like to express our sincere gratitude to the FOSSEE team at IIT Bombay for organising the Open Hardware Make-a-thon 2026. Their continuous efforts in promoting free and open-source tools have provided students like us with a meaningful platform to learn, experiment and innovate.

We are also thankful to the developers of Velxio for creating such a powerful and accessible multi-board simulation environment. It allowed us to design, test and refine a complete networked system with ease, and made the entire development process both efficient and enjoyable.

Finally, we extend our heartfelt thanks to the global open-source community. The freely available libraries, documentation and shared knowledge formed the true foundation of this project, and reminded us of the strength that comes from building openly and collaboratively.
