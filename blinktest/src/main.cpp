/*
  Uses a for loop to print numbers in various formats.
*/

#include "Arduino.h"

int ledPin = 3;
int myDelay = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(myDelay);
  digitalWrite(ledPin, LOW);
  delay(myDelay);
}