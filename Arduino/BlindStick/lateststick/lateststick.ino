// ---------------------------------------------------------------- //
// Arduino Blind Stick Code
// Features: Ultrasonic detection, Buzzer alert, Vibration feedback, LED indicators
// ---------------------------------------------------------------- //

// --- Pin Definitions ---
const int trigPin = 9;      // Ultrasonic Sensor Trig
const int echoPin = 10;     // Ultrasonic Sensor Echo
const int buzzerPin = 11;   // Buzzer
const int greenLed = 12;    // Safe indicator
const int redLed = 13;      // Danger indicator
const int motorPin = 7;     // Vibration Motor

// --- Variables ---
long duration;
int distance;
const int safetyDistance = 50; // Distance in cm to trigger alert

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Set Pin Modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(motorPin, OUTPUT);

  // Startup indication (optional check)
  digitalWrite(greenLed, HIGH); 
}

void loop() {
  // 1. Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 2. Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // 4. Calculate the distance
  // Speed of sound is 0.034 cm/us. Distance = (duration * speed) / 2
  distance = duration * 0.034 / 2;

  // 5. Print distance to Serial Monitor (Ctrl+Shift+M to view)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 6. Check for Obstacles
  if (distance <= safetyDistance && distance > 0) {
    // --- DANGER DETECTED ---
    digitalWrite(greenLed, LOW);   // Turn off safe light
    digitalWrite(redLed, HIGH);    // Turn on danger light
    digitalWrite(buzzerPin, HIGH); // Buzz
    digitalWrite(motorPin, HIGH);  // Vibrate
  } 
  else {
    // --- PATH IS CLEAR ---
    digitalWrite(greenLed, HIGH);  // Turn on safe light
    digitalWrite(redLed, LOW);     // Turn off danger light
    digitalWrite(buzzerPin, LOW);  // Stop Buzzing
    digitalWrite(motorPin, LOW);   // Stop Vibrating
  }
  
  // Small delay for stability
  delay(100); 
}