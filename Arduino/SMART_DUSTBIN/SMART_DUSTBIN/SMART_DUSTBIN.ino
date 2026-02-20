#include <Servo.h>

// Define the pins you provided
const int trigPin = 9;    
const int echoPin = 8;   
const int servoPin = 3;

// Create a servo object to control the servo motor
Servo lidServo;

// Variables for calculating distance
long duration;
int distance;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Define pin modes for the ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Attach the servo to its pin
  lidServo.attach(servoPin);
  
  // Set the initial position of the servo (Lid Closed)
  // You may need to change '0' to match your physical lid's closed position
  lidServo.write(0); 
}

void loop() {
  // 1. Send an ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 2. Read the echo pin (returns the sound wave travel time in microseconds)
  duration = pulseIn(echoPin, HIGH);
  
  // 3. Calculate the distance in centimeters
  // Speed of sound is 0.034 cm/us. Divide by 2 because the wave travels out and back.
  distance = duration * 0.034 / 2;
  
  // Print distance to Serial Monitor for testing
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // 4. Logic for the Smart Dustbin
  // If an object is closer than 30 cm (and greater than 0 to filter out errors)
  if (distance > 0 && distance <= 30) {
    lidServo.write(-80);  // Open the lid (90 degrees)
    delay(3000);         // Keep the lid open for 3 seconds
  } else {
    lidServo.write(0);   // Keep the lid closed (0 degrees)
  }
  
  // A small delay before taking the next measurement to ensure sensor stability
  delay(100); 
}