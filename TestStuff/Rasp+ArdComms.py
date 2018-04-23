import smbus
import time
import io
import fcntl

# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

def writeNumber(value):
    bus.write_byte(address, value)
    # bus.write_byte_data(address, 0, value)
    return -1

def readNumber():

    # I'm not familiar with the SMbus library, so you'll have to figure out how to
    # tell if any more bytes are available and when a transmission of integer bytes
    # is complete. For now, I'll use the boolean variable "bytes_available" to mean
    # "we are still transmitting a single value, one byte at a time"

    byte_list = []
    while bytes_available:
        # build list of bytes in an integer - assuming bytes are sent in the same
        # order they would be written. Ex: integer '123' is sent as '1', '2', '3'
        byte_list.append(bus.read_byte(address))

    # now recombine the list of bytes into a single string, then convert back into int
    number = int("".join([chr(byte) for byte in byte_list]))
    return number


while True:
    var = input('Enter 1 – 9: ')
    if not var:
        continue

    writeNumber(var)
    print 'RPI: Hi Arduino, I sent you ', var
    # sleep one second
    time.sleep(1)

    number = readNumber()
    print 'Arduino: Hey RPI, I received a digit ', number
    print
