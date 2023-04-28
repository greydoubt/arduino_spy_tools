/*
this code assumes that you have a camera module connected to the Arduino via a software serial connection. The code sends commands to the camera to wake it up, reset it, take a picture, and retrieve the image size. The PIR motion sensor is connected to a digital pin on the Arduino, and the LED is connected to another digital pin.

In the setup() function, the PIR motion sensor pin and the LED pin are set as input and output, respectively. The software serial communication with the camera is also started, and the camera is awakened and reset. The getCameraSize() function retrieves the size of the camera image, which is printed to the serial monitor.

In the loop() function, the PIR motion sensor is constantly checked for any motion. If motion is detected, the takePicture() function is called to capture an image from the camera, and the flashLED() function is called to flash the LED for a short amount of time.

Note that this is just an example code and may require modification to work with your specific camera and PIR motion sensor. You may also need to adjust the delay times to ensure proper operation.

*/


#include <SoftwareSerial.h>

// Define the digital pin to which the PIR motion sensor is connected
#define PIR_PIN 2

// Define the digital pin to which the LED is connected
#define LED_PIN 13

// Define the software serial pins for the camera
#define CAMERA_TX 10
#define CAMERA_RX 11

// Define the camera commands
#define CAMERA_WAKEUP "AA 0D 00 00 00 00 00 00 00 00 00 00 00 00 00 0D AA"
#define CAMERA_RESET "AA 08 00 00 00 00 00 00 00 00 00 00 00 08 AA"
#define CAMERA_SNAPSHOT "AA 05 00 00 00 00 00 00 00 00 00 00 00 05 AA"
#define CAMERA_GET_SIZE "AA 05 04 00 01 00 00 00 00 00 00 00 00 0A AA"

SoftwareSerial cameraSerial(CAMERA_RX, CAMERA_TX);

void setup() {
  // Set the PIR motion sensor pin as input
  pinMode(PIR_PIN, INPUT);
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  // Start the software serial communication with the camera
  cameraSerial.begin(38400);
  // Send the camera wakeup command
  sendCameraCommand(CAMERA_WAKEUP);
  delay(1000);
  // Send the camera reset command
  sendCameraCommand(CAMERA_RESET);
  delay(1000);
  // Print the camera size to the serial monitor
  Serial.println(getCameraSize());
}

void loop() {
  // If the PIR motion sensor detects a person, take a picture and flash the LED
  if (digitalRead(PIR_PIN) == HIGH) {
    takePicture();
    flashLED();
  }
}

void sendCameraCommand(String command) {
  // Convert the command string to a byte array
  byte cmd[command.length() / 3];
  for (int i = 0; i < command.length() / 3; i++) {
    cmd[i] = strtol(command.substring(i * 3, i * 3 + 2).c_str(), NULL, 16);
  }
  // Send the command to the camera
  for (int i = 0; i < sizeof(cmd); i++) {
    cameraSerial.write(cmd[i]);
  }
}

String getCameraSize() {
  // Send the "get size" command to the camera
  sendCameraCommand(CAMERA_GET_SIZE);
  // Read the response from the camera
  byte size[4];
  for (int i = 0; i < 4; i++) {
    while (cameraSerial.available() == 0);
    size[i] = cameraSerial.read();
  }
  // Return the size string
  return String(size[1]) + "x" + String(size[2]) + " " + String(size[3]) + "bpp";
}

void takePicture() {
  // Send the snapshot command to the camera
  sendCameraCommand(CAMERA_SNAPSHOT);
  // Wait for the camera to finish taking the picture
  delay(5000);
}

void flashLED() {
  // Turn on the LED
  digitalWrite(LED_PIN, HIGH);
  // Wait for a short amount of time
  delay(100);
  // Turn off the LED
  digitalWrite(LED_PIN, LOW);
}
