/*
uses a microphone sensor to detect the ambient sound levels and light up an LED according to the detected sound levels:

*/


// Define the analog pin to which the microphone sensor is connected
#define MIC_PIN A0

// Define the digital pin to which the LED is connected
#define LED_PIN 13

// Define the threshold value for the sound levels
#define THRESHOLD 500

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the microphone sensor
  int micValue = analogRead(MIC_PIN);
  // Print the analog value to the serial monitor
  Serial.println(micValue);
  // If the sound level is above the threshold, turn on the LED
  if (micValue > THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  // Wait for a short amount of time
  delay(10);
}
