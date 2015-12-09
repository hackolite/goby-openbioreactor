#!/usr/bin/python
import serial
import time
import threading
from optparse import OptionParser



def motor(time,motor):
    motor={'motor1':['s','e'],'motor2':['c','t'],'motor3':['v','y'],'motor4':['x','r']}
    parser = OptionParser()
    parser.add_option("-t", "--time", dest="time")
    parser.add_option("-m", "--motor", dest="motor")
    (options, args) = parser.parse_args()
    print options.motor
    ser = serial.Serial('/dev/ttyACM1', 9600, timeout=1000)
    time.sleep(2)
    ser.write(bytearray(motor[options.motor][0]))
    ser.close()  
    time.sleep(int(options.time))
    ser = serial.Serial('/dev/ttyACM1', 9600, timeout=1000)
    time.sleep(2)
    ser.write(bytearray(motor[options.motor][1]))
    ser.close()

if __name__ == '__main__':
	motor(time,motor)

