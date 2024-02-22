const int trigPin = 9;    // Trigger pin of the ultrasonic sensor
const int echoPin = 10;   // Echo pin of the ultrasonic sensor
const int buzzerPin = 8;  // Buzzer pin

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  long duration, distance;

  // Generate pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the echo to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Output the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an obstacle is within a certain range (adjust the range as needed)
  if (distance < 100) {
    // Alert the user with the buzzer
    tone(buzzerPin, 1000, 500);  // You can adjust the frequency and duration of the tone
  } else {
    noTone(buzzerPin);  // Turn off the buzzer if no obstacle is detected
  }

  delay(500);  // Add a delay to avoid rapid beeping
}
