#include "Arduino.h"

#define pwmPin1 3 //Pwm pin motor 1
#define in1 4 //Motor pin 1
#define in2 5 //Motor pin 2

const byte numBytes = 32;
byte receivedBytes[numBytes];
bool newData = false;
byte numReceived = 0; 

int read;
void receiveData();
void parseReceivedData();

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
  receiveData();
  parseReceivedData();
  // if(Serial.available() > 0) {
  //   Serial.println("Dado Lido");
  //   read = Serial.read();
  //   Serial.println(read);

  //   rmotor_callback(read);
  // }
    
}

void receiveData() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  byte startMarker = 0x3C;
  byte endMarker = 0x3E;
  byte rb;

  while (Serial.available() > 0 && newData == false) {
          rb = Serial.read();

          if (recvInProgress == true) {
              if (rb != endMarker) {
                  receivedBytes[ndx] = rb;
                  ndx++;
                  if (ndx >= numBytes) {
                      ndx = numBytes - 1;
                  }
              }
              else {
                  receivedBytes[ndx] = '\0'; // terminate the string
                  recvInProgress = false;
                  numReceived = ndx;  // save the number for use when printing
                  ndx = 0;
                  newData = true;
              }
          }

          else if (rb == startMarker) {
              recvInProgress = true;
          }
      }
}

void parseReceivedData() {
    if (newData == true) {
        // Serial.print("This just in (DEC values)... ");
        for (byte n = 0; n < numReceived; n++) {
            Serial.print(receivedBytes[n], DEC);
            Serial.print(' ');
        }
        int variavel = (receivedBytes[1] << 8) + receivedBytes[0];
        Serial.print(variavel);
        rmotor_callback(variavel);
        newData = false;
    }
}