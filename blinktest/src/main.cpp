#include "Arduino.h"

//RIGHT MOTOR
#define ena_pin 5 
#define in1_pin 9 
#define in2_pin 8 
//LEFT MOTOR
#define enb_pin 6 
#define in3_pin 4 
#define in4_pin 3

int vel;
int setvel = 200; //Set velocity manually
int maxvel = 255; //Max pwm vel

void setup() {
  pinMode(ena_pin, OUTPUT);
  pinMode(in1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);

  pinMode(enb_pin, OUTPUT);
  pinMode(in3_pin, OUTPUT);
  pinMode(in4_pin, OUTPUT);

}

void loop () {
  delay(2000);

  digitalWrite(in1_pin, HIGH);
  digitalWrite(in2_pin, LOW);

  digitalWrite(in3_pin, HIGH);
  digitalWrite(in4_pin, LOW);

  analogWrite(ena_pin, 160);
  analogWrite(enb_pin, 160);

  delay(2000);

  digitalWrite(in1_pin, HIGH);
  digitalWrite(in2_pin, LOW);

  digitalWrite(in3_pin, HIGH);
  digitalWrite(in4_pin, LOW);

  analogWrite(ena_pin, 150);
  analogWrite(enb_pin, 150);

  delay(2000);

  digitalWrite(in1_pin, HIGH);
  digitalWrite(in2_pin, LOW);

  digitalWrite(in3_pin, HIGH);
  digitalWrite(in4_pin, LOW);

  analogWrite(ena_pin, 140);
  analogWrite(enb_pin, 140);

  delay(2000);

  digitalWrite(in1_pin, HIGH);
  digitalWrite(in2_pin, LOW);

  digitalWrite(in3_pin, HIGH);
  digitalWrite(in4_pin, LOW);

  analogWrite(ena_pin, 130);
  analogWrite(enb_pin, 130);
  
}