import serial
import time

arduino = serial.Serial(port='COM7', baudrate=9600, timeout=.1)
time.sleep(2)

x = "R3"

arduino.write(bytes(x, 'utf-8'))
time.sleep(1)
x = "8.03 1.53 10"

arduino.write(bytes(x, 'utf-8'))
time.sleep(5)
x = "-21.3 -58.8 10"

arduino.write(bytes(x, 'utf-8'))
time.sleep(5)
x = "-42.47 4.2 10"

arduino.write(bytes(x, 'utf-8'))

time.sleep(15)



