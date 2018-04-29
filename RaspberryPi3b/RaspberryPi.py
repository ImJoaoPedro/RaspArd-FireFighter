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
debugInput = [65, 55, 10, 10, 125, 125, 5, 2000, 1500]

#try import in case sudo is needed
import smbus
import serial
import time
try:
    import RPi.GPIO as GPIO
    import lcd.LCD-i2c-lib
except RuntimeError:
    print("error importing, try sudo")

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
slaveAddress = 0x??

#LCD
lcd = I2C_LCD_driver.lcd()
lcddisplay = ""
if (mode == 1):
    lcd.lcd_display_string(lcddisplay, 1)
elif (mode == 2):
    lcd.lcd_display_string("safe", 1)
elif (mode == 3):
    lcd.lcd_display_string("", 1)

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
    ardInput = input.split(',')
    lcd.lcd_display_string(ardInput[1] + ardInput[0], 1)
    print(ardInput)

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

def sendMotors(direction):
    if(direction == 'w'):

    elif(direction == 'a'):

    elif(direction == 's'):

    elif(direction == 'd'):

    elif(direction == 'x'):

def locateFlame():
    x = ardInput[2]
    y = ardInput[3]
    print("x coordinate: " + x"\ny coordinate: " + y)
    flameProx = ardInput[6]
    print("\nthe flame sensor is sensing: " + flameProx)

#flag for loop
active = True

#loop
if (mode == 1):
    while active:
        read_ser=str(ser.readline())
        assignInput(read_ser)
        locateFlame()
        move()
elif (mode == 2):
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
