'''This Python code uses the serial library to communicate with the Arduino and the camera module via serial communication. The PIR motion sensor pin and the LED pin are defined as constants at the beginning of the code. The camera commands are also defined as constants.

The send_command() function sends a command to the Arduino or the camera by writing a byte array to the serial port. The get_camera_size() function retrieves the size of the camera image by sending the CAMERA_GET_SIZE command to the Arduino and reading the response. The take_picture() function sends the CAMERA_SNAPSHOT command to the Arduino to take a picture. The flash_led() function sends commands to turn on and off the LED connected to the Arduino.

In the with block, the Python code initializes the camera module by sending the CAMERA_WAKEUP and CAMERA_RESET commands. The camera size is then printed to the console. The code then enters an infinite loop and waits for the Arduino to send a signal indicating that motion has been detected by the PIR motion sensor. When motion is detected, the take_picture() and flash_led() functions are called.'''

import serial
import time

# Define the serial port and baud rate for the Arduino
SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 9600

# Define the digital pin to which the PIR motion sensor is connected
PIR_PIN = 2

# Define the digital pin to which the LED is connected
LED_PIN = 13

# Define the camera commands
CAMERA_WAKEUP = 'AA 0D 00 00 00 00 00 00 00 00 00 00 00 00 00 0D AA'
CAMERA_RESET = 'AA 08 00 00 00 00 00 00 00 00 00 00 00 08 AA'
CAMERA_SNAPSHOT = 'AA 05 00 00 00 00 00 00 00 00 00 00 00 05 AA'
CAMERA_GET_SIZE = 'AA 05 04 00 01 00 00 00 00 00 00 00 00 0A AA'

# Define the serial port and baud rate for the camera
CAMERA_SERIAL_PORT = '/dev/ttyUSB0'
CAMERA_BAUD_RATE = 38400

ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

def send_command(cmd):
    ser.write(bytearray.fromhex(cmd))

def get_camera_size():
    send_command(CAMERA_GET_SIZE)
    size = ser.read(4)
    return f'{size[1]}x{size[2]} {size[3]}bpp'

def take_picture():
    send_command(CAMERA_SNAPSHOT)
    time.sleep(5)

def flash_led():
    send_command('1')
    time.sleep(0.1)
    send_command('0')

with serial.Serial(CAMERA_SERIAL_PORT, CAMERA_BAUD_RATE) as camera:
    camera.write(bytearray.fromhex(CAMERA_WAKEUP))
    time.sleep(1)
    camera.write(bytearray.fromhex(CAMERA_RESET))
    time.sleep(1)
    print(get_camera_size())

    while True:
        if ser.read(1) == b'1':
            take_picture()
            flash_led()
