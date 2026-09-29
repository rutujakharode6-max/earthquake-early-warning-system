#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define BUZZER      25
#define LED_GREEN   12
#define LED_YELLOW  13
#define LED_RED     14

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  Wire.begin(21, 22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (1) delay(10);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("QuakeMesh Node-2");
  display.println("Listening...");
  display.display();

  Serial.println("Node-2 Ready");
}

void loop() {
  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    if (msg == "ALERT") {
      digitalWrite(LED_RED, HIGH);
      digitalWrite(BUZZER, HIGH);

      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("QuakeMesh Node-2");
      display.println("ALERT RECEIVED!");
      display.println("From Node-1");
      display.display();

      delay(4000);  // Keep alarm for 4 seconds

      digitalWrite(LED_RED, LOW);
      digitalWrite(BUZZER, LOW);
    }
  }
  delay(30);
}
