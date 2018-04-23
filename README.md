# RaspArd-FireFighter

    Project using a RaspberryPi and 2 Arduinos to control a Cherokey 4WD in order to put out fires.

# TODO

    - finish a better readme
    - everything else

# Current Pin Configuration
    
    RaspberryPi
    2 - SCL I2C (RoMeu)
    3 - SDA I2C (RoMeu)
    4 - Vim RoMeu
    5 - GND RoMeu

    ArduinoMega
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

    ArduinoRoMeu
    I2C - LCD
    Digital
    2 - Green Button
    3 - Red Button
    4 - Siren (blue/red)
    5 - Servo Camera IRCamera
    6 - PWM Cherokey
    7 - PWM Cherokey
    9 - PWM Cherokey
    10 - PWM Cherokey
    Analog
    0 - Potenciometer (Test Knob)
    1 - Sound Meter
    2 - Y Axis Accelerometer
    3 - X Axyx Accelerometer

# Sensors Description
