#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_ADDRESS 0x3C
#define OLED_RESET -1

#define MOISTURE_PIN A0
#define DIGITAL_PIN 2

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {

  Serial.begin(9600);

  pinMode(DIGITAL_PIN, INPUT);

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED NOT FOUND!");
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(15, 10);
  display.println("PLANT");

  display.setCursor(15, 35);
  display.println("SENSOR");

  display.display();

  delay(2000);
}

void loop() {

  // Read moisture sensor
  int rawValue = analogRead(MOISTURE_PIN);
  int digitalValue = digitalRead(DIGITAL_PIN);

  /*
     Moisture percentage

     1023 = dry
     300  = wet

     Change these numbers after calibration.
  */
  int moisture = map(rawValue, 1023, 300, 0, 100);

  moisture = constrain(moisture, 0, 100);

  // Serial Monitor
  Serial.print("Raw: ");
  Serial.print(rawValue);

  Serial.print(" | Moisture: ");
  Serial.print(moisture);
  Serial.print("%");

  Serial.print(" | D2: ");
  Serial.println(digitalValue);

  // OLED
  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("PLANT MOISTURE");

  // Percentage
  display.setTextSize(3);
  display.setCursor(25, 15);
  display.print(moisture);
  display.println("%");

  // Status
  display.setTextSize(1);
  display.setCursor(0, 50);

  if (moisture < 30) {
    display.println("STATUS: DRY");
  }
  else if (moisture < 70) {
    display.println("STATUS: GOOD");
  }
  else {
    display.println("STATUS: WET");
  }

  display.display();

  delay(1000);
}