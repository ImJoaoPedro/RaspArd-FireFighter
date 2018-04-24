"""
Raspberry Pi code to receive input from 2 different arduinos
"""

#try import in case sudo is needed
import serial
import time
try:
    import RPi.GPIO as GPIO
except RuntimeError:
    print("error importing, try sudo")

#change ACM number as found from ls /dev/tty/ACM*
#consider ser.port = input()
#check channel irl
ser=serial.Serial()
ser.port = "/dev/ttyACM0"
ser.baudrate=9600
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.IN)

#flag for loop
active = True

#loop
while active:
    read_ser=ser.readline()
    print(read_ser)
    print(GPIO.getmode())
