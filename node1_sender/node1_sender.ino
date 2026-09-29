#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define BUZZER      25
#define LED_GREEN   12
#define LED_YELLOW  13
#define LED_RED     14

#define MPU_ADDR 0x68

float LIGHT  = 1.4;
float MEDIUM = 2.4;
float STRONG = 3.3;

int16_t AcX, AcY, AcZ;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  Wire.begin(21, 22);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("QuakeMesh Node-1");
  display.println("Ready...");
  display.display();
}

void loop() {
  // Read raw data from MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Convert to g (approximate)
  float x = AcX / 16384.0;
  float y = AcY / 16384.0;
  float z = AcZ / 16384.0;

  float magnitude = sqrt(x*x + y*y + z*z);

  // Turn everything off first
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(BUZZER, LOW);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("QuakeMesh Node-1");
  display.print("Mag: ");
  display.println(magnitude, 2);

  if (magnitude > STRONG) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(BUZZER, HIGH);
    display.println("STRONG ALERT!");
    display.println("Sending to Node-2");
    Serial.println("ALERT");
  }
  else if (magnitude > MEDIUM) {
    digitalWrite(LED_YELLOW, HIGH);
    display.println("MEDIUM WARNING");
  }
  else if (magnitude > LIGHT) {
    digitalWrite(LED_GREEN, HIGH);
    display.println("Light shake");
  }
  else {
    display.println("SAFE");
  }

  display.display();
  delay(200);
}
