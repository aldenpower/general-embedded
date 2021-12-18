#include "Arduino.h"

#define pwmPin1 3 //Pwm pin motor 1
#define in1 4 //Motor pin 1
#define in2 5 //Motor pin 2

int vel;
int setvel = 150; //Set velocity manually
int maxvel = 255; //Max pwm vel

void setup() {
  //PWM
  pinMode(pwmPin1, OUTPUT);
  
  pinMode(mla, OUTPUT);
  pinMode(mlb, OUTPUT);

  // digitalWrite(mla, LOW);
  // digitalWrite(mlb, LOW);
  // analogWrite(velmotor, vel);

}

void loop () {
  vel = maxvel;
  analogWrite(pwmPin1, vel);

  digitalWrite(mla, HIGH);
  digitalWrite(mlb, LOW);

}