"""
Raspberry Pi code to receive input from 2 different arduinos

TO DO:
- i2c controller to PWM
- sensors calculations
- etc

"""
#debug options
print("1 - Normal\n2 - No LCD\n3 - Debug mode")
mode = input("Set execution mode: ")

#debug mode with preset ardInput
debugInput = "65, 55, 10, 10, 125, 125, 5, 2000, 1500"

#try import in case sudo is needed
from smbus import SMBus
import serial
import time
import RPi.GPIO as GPIO
import I2C_LCD_driver

#ArduinoMega
#change ACM number as found from ls /dev/tty/ACM*
#consider ser.port = input()
#check channel irl
ser=serial.Serial()
ser.port = "/dev/ttyACM0"
ser.baudrate=9600
ser.open()
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.IN)
print(GPIO.getmode())       #testing purposes

#String To Bytes
def StringToBytes(val):
    retVal = []
    for c in val:
            retVal.append(ord(c))
    return retVal

#ArduinoRomeo
bus = SMBus(1)
slaveAddress = "0x??"
"""
#LCD
lcd = I2C_LCD_driver.lcd()
lcddisplay = ""
if mode == 1:
    lcd.lcd_display_string(lcddisplay, 1)
elif mode == 2:
    lcd.lcd_display_string("safe", 1)
elif mode == 3:
    lcd.lcd_display_string("", 1)
"""
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

def assignInput(input):
    #ardInput.clear()
    ardInput = input.split(',')
    return ardInput
    #lcd.lcd_display_string(ardInput[1] + ardInput[0], 1)

def sendMotors(direction):
    if direction == 'w':
        print(direction)
    elif direction == 'a':
        print(direction)
    elif direction == 's':
        print(direction)
    elif direction == 'd':
        print(direction)
    elif direction == 'x':
        print(direction)

def move():
    leftDistance = ardInput[1]
    rightDistance = ardInput[0]
    direction = ''
    if(mode != 3):
        sendMotors(direction)
    else:
        sendMotors('w')
        sendMotors('a')
        sendMotors('s')
        sendMotors('d')
        sendMotors('x')

def locateFlame():
    x = ardInput[2]
    y = ardInput[3]
    print("x coordinate: " + x)
    print("\ny coordinate: " + y)
    flameProx = ardInput[6]
    print("\nthe flame sensor is sensing: " + flameProx)

#flag for loop
active = True

#loop
#if (mode == 1):
while active:
    read_ser=str(ser.readline())
    #print(read_ser)
    ardInput = assignInput(read_ser)
    #assignInput(read_ser)
    print(ardInput)
    if ((len(ardInput)) == 10):
        locateFlame()
        #move()
'''elif (mode == 2):
    while active:
        read_ser=str(ser.readline())
        assignInput(read_ser)
        locateFlame()
        move()
elif (mode == 3):
    while active:
        assignInput(debugInput)
        locateFlame()
        move()
'''