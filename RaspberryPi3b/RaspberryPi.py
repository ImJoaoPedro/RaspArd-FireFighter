"""
Raspberry Pi code to receive input from 2 different arduinos

TO DO:
- i2c controller to PWM
- sensors calculations
- etc

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

#def input from ArduinoMega
#input:
#[0]Right Distance
#[1]Left Distance
#[2]X flame coordinate
#[3]Y flame coordinate
#[4]Left LDR Pin
#[5]Right LDR Pin
#[6]Flame Sensor Pin
#[7]Axis X
#[8]Axis Y
ardInput = []
def assignInput(input):
    ardInput = input.split(",")

#flag for loop
active = True

#loop
while active:
    read_ser=ser.readline()
    print(read_ser)             #testing purposes
    assignInput(read_ser)
    print(ardInput)             #testing purposes

    print(GPIO.getmode())       #testing purposes
