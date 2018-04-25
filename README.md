# RaspArd-FireFighter

    Project using a RaspberryPi and 2 Arduinos to control a Cherokey 4WD in order to put out fires.

# TODO

    - Finish a better readme
    - Everything else
    - Create roadmap

# Current Pin Configuration
    
    RaspberryPi
    2 - SCL I2C (RoMeu)
    3 - SDA I2C (RoMeu)
    4 - Vim RoMeu
    5 - GND RoMeu

    ArduinoMega
    I2C - Pixy camera
    Digital
    2 - Echo US
    3 - Trig US (yellow)
    4 - Echo US
    5 - Trig US (black)
    20 - SDA I2C (IRCamera)
    21 - SCL I2C (IRCamera)
    Analog
    0 - LDR Flor Left
    1 - LDR Flor Right
    2 - Flame Sensor
    3 - X Axyx Accelerometer
    4 - Y Axis Accelerometer

    ArduinoRoMeu
    I2C - LCD
    Digital
    2 - Green Button
    3 - Red Button
    4 - Siren (blue/red)
    5 - Servo Camera IRCamera
    6 - Left Motor Cherokey PWM (Speed Control)
    7 - Left Motor Cherokey (Direction Control)
    9 - Right Motor Cherokey (Direction Control)
    10 - Right Motor Cherokey PWM (Speed Control)
    Analog
    0 - Potenciometer (Test Knob)
    1 - Sound Meter
    //2 - Y Axis Accelerometer
    //3 - X Axyx Accelerometer

# Sensors Configuration

    RaspberryPi receives:
    - Everything from ArduinoMega sent via Serial
    - Everything from ArduinoRoMeu sent via I^2C
    
    RaspberryPi sends:
    - Single characters to ArduinoRoMeu indicating the motor control (w,a,s,d,x->to stop motors) 
    - Messages to LCD via I^2C

    ArduinoMega receives:
    - Flame Sesor values (int)
    - Ultra Sound values (2 x int) 
    - IR Camera byte streams->(int[9])
    - LDR values (2 x int)
    -Pixi Camera signal (change to pi?)
    
    ArduinoMega sends (via Serial):
    - Ultra sound values to Pi
    - LDR values
    - Flame Sensor value
    - Triplet indicating the camera value of the flame (X,Y) if detected

    ArduinoRoMeu receives :
    - Accelerometer ( 2 x int) (X,Y) values
    - Potenciometer (int (via analog))
    - Buttons (RED and GREEN) (2 x boolean)
    - Sound (int)
   
    
    ArduinoRoMeu sends:
    - (To motor Drivers) Motor control Cherokey
    - (To Blue LED) Siren signal 
    - (To Pi) Potenciometer value, Buttons values, Sound value

<<<<<<< HEAD
# Sensors Description (Work In Progress)

    IR Camera
    returns (x, y, int), int goes from 0 (Hot) to 1023 (Cold)

    UV Sensor
    - 
    
    Buttons

    LDRs

    Accelerometer

    Potenciometer

    Sound Meter

    PWM Cherokey

    LCD

    Siren
=======
# Sensors Description :shipit:
>>>>>>> ebe2b5e2fcd8be92f8e6930265e8bd675f7a82b4

# Roadmap :shipit:

