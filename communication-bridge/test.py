import serial

ports = serial.tools.list_ports.comports()

print(ports)