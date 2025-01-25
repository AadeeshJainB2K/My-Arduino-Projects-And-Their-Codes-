#include <Servo.h>

// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

// Create Servo object
Servo lidServo;

// Define servo pin
const int servoPin = 3;

// Distance threshold to open the dustbin lid (in cm)
const int distanceThreshold = 20;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set ultrasonic sensor pins as input/output
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach the servo to the defined pin
  lidServo.attach(servoPin);
  
  // Initialize the servo position (lid closed)
  lidServo.write(0);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  long duration = measureDistance();
  int distance = duration * 0.034 / 2; // Convert to cm
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Open lid if distance is within the threshold
  if (distance > 0 && distance < distanceThreshold) {
    lidServo.write(180); // Open the lid
    delay(3000);        // Wait for 3 seconds
    lidServo.write(0);  // Close the lid
  }

  delay(200); // Short delay for stability
}

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  // Send a 10-microsecond pulse to the TRIG pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the pulse duration from the ECHO pin
  return pulseIn(echoPin, HIGH);
}
