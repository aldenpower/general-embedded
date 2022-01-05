#include "Arduino.h"

// Range of the integer (-32768 to 32767)
// Size o the integer is 16-bit 2 bytes

const unsigned int MAX_MESSAGE_LENGHT = 12;

void setup(){
    Serial.begin(9600);
}
 
void loop(){
    // check to see if anything is available in the serial receive buffer
    while (Serial.available() > 0) //available return the number of bytes to be read
    {
        // create a place to hold the incoming message
        static char message[MAX_MESSAGE_LENGHT];
        static unsigned int message_pos = 0;

        // read the next available byte in the serial receiver buffer
        char intByte = Serial.read();

        // message coming check no terminating character new line
        if (intByte != '\n' && (message_pos < MAX_MESSAGE_LENGHT - 1))
        {
            // add the coming byte to the message
            message[message_pos] = intByte;
            message_pos++;   
        }
        else
        {
            // add null character to string
            message[message_pos] = '\0';
            Serial.println(message);

            // reset for the next message
            message_pos = 0;
        }
        
    }
    
    
}