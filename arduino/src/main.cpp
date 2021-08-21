#include <Arduino.h>
#include<define.h>

void setup()
{
  Serial.begin(9600);
  setsonar(echopin, trigpin);
  setled(activebuzzer);
}

void loop() 
{
  float distance = sonar(echopin, trigpin);
  
  if (distance < 100)
  {
    digitalWrite(activebuzzer, HIGH);
  }
  else
  {
    digitalWrite(activebuzzer, LOW);
  }
}