#include "Arduino.h"

// Range of the integer (-32768 to 32767)
// Size o the integer is 16-bit 2 bytes
int x = 12;

void setup(){
    Serial.begin(9600);
}
 
void loop(){
   Serial.print(x);
   delay(1000); 
}