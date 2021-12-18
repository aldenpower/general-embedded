#include "Arduino.h"

#define pwmPin1 3 //Pwm pin motor 1
#define in1 4 //Motor pin 1
#define in2 5 //Motor pin 2

int vel;
int setvel = 150; //Set velocity manually
int maxvel = 255; //Max pwm vel

void setup() {
  pinMode(pwmPin1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop () {
  vel = maxvel;
  analogWrite(pwmPin1, vel);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}