#include "Arduino.h"

#define pwmPin1 3 //Pwm pin motor 1
#define in1 4 //Motor pin 1
#define in2 5 //Motor pin 2

int read;

void rmotor_callback(int powerlevel) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(pwmPin1, powerlevel);
};

void setup()
{
  // initialize serial:
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available() > 0) {
    read = Serial.read();
    Serial.println(read, DEC);
    rmotor_callback(read);
    Serial.println("feito");
  }
}