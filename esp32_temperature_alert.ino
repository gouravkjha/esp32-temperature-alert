
/*
  ESP32 Temperature Alert System
  --------------------------------
  This code uses a DallasTemperature sensor connected via OneWire protocol to read temperature.
  Based on the temperature range, it lights up different LEDs and activates a buzzer in critical situations.

  - Green LED: Normal temperature (10°C < temp <= 45°C)
  - Orange LED: High temperature (45°C < temp < 60°C)
  - Red LED + Buzzer: Critical temperature (temp >= 60°C)
  - White LED + Buzzer: Very low temperature (temp <= 10°C)
*/

#include <OneWire.h>
#include <DallasTemperature.h>

#define LEDR 23   // Red LED pin
#define LEDG 15   // Green LED pin
#define LEDW 20   // White LED pin
#define LEDO 21   // Orange LED pin
#define BUZZER 24 // Buzzer pin

#define TEMPERATURE 32 // Temperature sensor data pin

OneWire oneWire(TEMPERATURE);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  sensors.begin();

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDW, OUTPUT);
  pinMode(LEDO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDW, LOW);
  digitalWrite(LEDO, LOW);
  digitalWrite(BUZZER, LOW);

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC > 45 && tempC < 60) {
    Serial.println("Orange Alert: Temperature too High");
    Serial.print(tempC);
    Serial.println(" °C");
    digitalWrite(LEDO, HIGH);
  }
  else if (tempC >= 60) {
    Serial.println("Red Alert: Temperature Extremely High (Non-survivable)");
    Serial.print(tempC);
    Serial.println(" °C");
    digitalWrite(LEDR, HIGH);
    digitalWrite(BUZZER, HIGH);
  }
  else if (tempC > 10 && tempC <= 45) {
    Serial.println("Normal Temperature");
    Serial.print(tempC);
    Serial.println(" °C");
    digitalWrite(LEDG, HIGH);
  }
  else if (tempC <= 10) {
    Serial.println("White Alert: Temperature too Low");
    Serial.print(tempC);
    Serial.println(" °C");
    digitalWrite(LEDW, HIGH);
    digitalWrite(BUZZER, HIGH);
  }

  delay(2000); // Wait 2 seconds before reading temperature again
}
