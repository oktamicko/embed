#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature;

const int fanPin = 8;
int state = 0;

void setup() {
  lcd.begin();
  dht.begin();
  pinMode(fanPin, OUTPUT);
}

void loop() {
  delay(2000);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  printLCD();

  if (humidity < 65 || state == 1) {
    digitalWrite(fanPin, HIGH);
    state = 1;
    if (humidity > 75) {
      digitalWrite(fanPin, LOW);
      state = 0;
    }
  } else {
    state = 0;
  }
}

void printLCD() {
  lcd.setCursor(0, 0); lcd.print("Humidity: ");
  lcd.setCursor(11, 0); lcd.print(humidity);
  lcd.setCursor(16, 0); lcd.print("%");

  lcd.setCursor(0, 1); lcd.print("Suhu: ");
  lcd.setCursor(7, 1); lcd.print(temperature);
  lcd.setCursor(10, 1); lcd.print("C");
}
