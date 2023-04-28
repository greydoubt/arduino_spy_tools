#uses a microphone sensor to detect the ambient sound levels and light up an LED according to the detected sound levels:

import serial
import pygame

# Initialize Pygame
pygame.init()
# Set the screen size
screen = pygame.display.set_mode((640, 480))

# Open the serial port
ser = serial.Serial('COM3', 9600)

# Run the game loop
while True:
    # Read the serial data
    data = ser.readline().strip().decode('utf-8')
    # Parse the data as an integer
    try:
        value = int(data)
    except ValueError:
        continue
    # Calculate the brightness of the screen based on the sound level
    brightness = max(min(value, 1023), 0) / 1023
    # Set the screen color
    screen.fill((int(255 * brightness), int(255 * brightness), int(255 * brightness)))
    # Update the screen
    pygame.display.flip()
