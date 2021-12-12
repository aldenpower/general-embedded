#!/usr/bin/python3

import serial

# ser = serial.Serial()
# ser.baudrate = 9600
# ser.port = '/dev/ttyACM0'

port = serial.Serial("/dev/ttyACM0", 9600)

while True:
    # port.read will print 1 byte at a time
    string = port.read(2) # Change for 2 bytes at a time
    print(string)