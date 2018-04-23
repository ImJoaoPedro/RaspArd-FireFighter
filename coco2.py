import time
import smbus

DEV_ADDR = 0x58

i2c = smbus.SMBus(1)

i2c.write_byte_data(DEV_ADDR, 0x30, 0x01)
time.sleep(.01)

i2c.write_byte_data(DEV_ADDR, 0x30, 0x08)
time.sleep(.01)

i2c.write_byte_data(DEV_ADDR, 0x06, 0x90)
time.sleep(.01)

i2c.write_byte_data(DEV_ADDR, 0x08, 0xC0)
time.sleep(.01)

i2c.write_byte_data(DEV_ADDR, 0x1A, 0x40)
time.sleep(.01)

i2c.write_byte_data(DEV_ADDR, 0x33, 0x33)
time.sleep(.11)

while True:
   i2c.write_byte(DEV_ADDR, 0x36)
   data = i2c.read_i2c_block_data(DEV_ADDR, 0x36, 16);
   print data
   x = [0x00]*4
   y = [0x00]*4
   x[0]  = data[1]
   x[0] += (data[3] & 0x30) << 4 
   y[0]  =  data[2]
   y[0] += (data[3] & 0xC0) << 2
   x[1]  = data[4]
   x[1] += (data[6] & 0x30) << 4
   y[1]  = data[5]
   y[1] += (data[6] & 0xC0) << 2
   x[2]  = data[7]
   x[2] += (data[9] & 0x30) << 4
   y[2]  = data[8]
   y[2] += (data[9] & 0xC0) << 2
   x[3]  = data[10]
   x[3] += (data[12] & 0x30) << 4
   y[3]  = data[11]
   y[3] += (data[12] & 0xC0) << 2
   print x
   print y
   time.sleep(1.0)
