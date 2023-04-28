// Define the analog pin to which the light sensor is connected
#define SENSOR_PIN A0

// Define the digital pin to which the LED is connected
#define LED_PIN 13

// Define the threshold value for the light levels
#define THRESHOLD 500

void setup() {
  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);
  // Start the serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the light sensor
  int sensorValue = analogRead(SENSOR_PIN);
  // Print the analog value to the serial monitor
  Serial.println(sensorValue);
  // If the light level is above the threshold, turn on the LED
  if (sensorValue > THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    // Wait for a short amount of time
    delay(1000);
    // Turn off the LED
    digitalWrite(LED_PIN, LOW);
  }
}
