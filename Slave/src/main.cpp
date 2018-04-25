// Chandler Bachman - 669993737
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <lcd.hpp>
#include <console.hpp>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 10, d7 = 9;
LCD lcd(rs, en, d4, d5, d6, d7);

const int potent = A0;
Console serial(false);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16);
  serial.begin();

  pinMode(13, OUTPUT);

  Serial.println("ready");
}


void loop() {
  lcd.print();
  delay(5);

  if (serial.ready()) {
    String input = serial.get();
    Serial.println("Got Data!");
    lcd.top(input);
  }
}
