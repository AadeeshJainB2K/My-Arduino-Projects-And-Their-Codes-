const int rainSensorPin = A0; // Analog pin connected to the rain sensor
const int buzzerPin = 9; // Digital pin connected to the buzzer

bool isRaining = false; // Flag to track rain status

void setup() {
  pinMode(rainSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(rainSensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  // Adjust this threshold value based on your sensor and environment
  int threshold = 300;
  
  if (sensorValue < threshold) {
    if (!isRaining) {
      isRaining = true;
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      Serial.println("Rain detected! Alarm activated!");
    }
  } else {
    if (isRaining) {
      isRaining = false;
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      Serial.println("Rain stopped! Alarm deactivated!");
    }
  }
  
  delay(100); // Adjust delay based on your project's requirements
}
