/*
  Earthquake Early Warning - Single Node Firmware (MVP)
  FOSSEE Open Hardware Make-A-Thon 2026

  Hardware: ESP32 + MPU6050 (accelerometer) + SSD1306 OLED + buzzer + relay

  What this does:
  1. Reads acceleration from the MPU6050 continuously
  2. Runs a simple STA/LTA (short-term average vs long-term average) check
     to detect a sudden spike in vibration energy against the background
  3. When the spike is big enough, it sounds the buzzer and fires the
     relay (which you'll wire to a demo solenoid/servo)
  4. Shows live status on the OLED

  IMPORTANT: TRIGGER_RATIO below is NOT tuned yet. You must calibrate it
  yourself using manual shakes and, later, your shake table. Start around
  3-4 and adjust from there. Write down what you land on for your report.
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---- Pin setup ----
const int BUZZER_PIN = 25;
const int RELAY_PIN = 26;

// ---- Devices ----
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// ---- STA/LTA detection settings ----
// These are exponential moving averages, not fixed windows - simpler to
// run on a microcontroller with very little memory.
float sta = 0;                 // short-term average (reacts fast)
float lta = 0;                 // long-term average (background level)
const float STA_ALPHA = 0.30;  // higher = reacts faster to recent samples
const float LTA_ALPHA = 0.01;  // lower = represents a slower, calmer baseline
float TRIGGER_RATIO = 3.5;     // <-- TUNE THIS after testing

// ---- Alarm state ----
bool alarmActive = false;
unsigned long alarmStartTime = 0;
const unsigned long ALARM_DURATION_MS = 5000;

void setup() {
  Serial.begin(115200);
  delay(300);

  Wire.begin(); // default ESP32 I2C pins: SDA=21, SCL=22

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found - check wiring (SDA/SCL/VCC/GND).");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 ready.");

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found - check wiring, continuing without it.");
  } else {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    showStatus("Monitoring...");
  }
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Total acceleration magnitude, with gravity (~9.8 m/s^2) roughly removed
  // so that "at rest" reads close to zero.
  float mag = sqrt(a.acceleration.x * a.acceleration.x +
                    a.acceleration.y * a.acceleration.y +
                    a.acceleration.z * a.acceleration.z) - 9.8;
  float energy = mag * mag; // squaring emphasizes spikes over background noise

  // Update the two running averages
  sta = STA_ALPHA * energy + (1 - STA_ALPHA) * sta;
  lta = LTA_ALPHA * energy + (1 - LTA_ALPHA) * lta;

  float ratio = (lta > 0.001) ? (sta / lta) : 0;

  if (!alarmActive && ratio > TRIGGER_RATIO) {
    triggerAlarm(ratio);
  }
  if (alarmActive && millis() - alarmStartTime > ALARM_DURATION_MS) {
    stopAlarm();
  }

  // Print for the Serial Plotter/Monitor - watch this while tuning
  Serial.print("STA:"); Serial.print(sta, 3);
  Serial.print(" LTA:"); Serial.print(lta, 3);
  Serial.print(" Ratio:"); Serial.println(ratio, 2);

  delay(20); // roughly 50 samples per second
}

void triggerAlarm(float ratio) {
  alarmActive = true;
  alarmStartTime = millis();
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(RELAY_PIN, HIGH); // fires the demo solenoid/servo
  showStatus("ALERT! ratio=" + String(ratio, 1));
  Serial.println(">>> POSSIBLE EARTHQUAKE SIGNAL DETECTED <<<");
}

void stopAlarm() {
  alarmActive = false;
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  showStatus("Monitoring...");
}

void showStatus(String msg) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("EEW Node v0.1");
  display.println("-------------");
  display.println(msg);
  display.display();
}
