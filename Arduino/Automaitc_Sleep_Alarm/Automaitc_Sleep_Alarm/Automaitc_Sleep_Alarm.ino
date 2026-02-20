// Complete Sunrise Alarm Code with Beep and Lockout

const int ldrPin = A0;
const int buzzerPin = 10;
const int buttonPin = 2;

// Thresholds for your specific LDR readings
const int lightThreshold = 100; // Alarm triggers when light drops below 100
const int darkThreshold = 700;  // System resets when light goes above 700

// Logic flags
bool alarmRinging = false;
bool alreadyWokeUpToday = false; 

// Timer variables for the beeping effect
unsigned long previousMillis = 0; 
const long beepInterval = 500; // Beep speed (500 milliseconds)
int buzzerState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  
  // Uses internal pull-up resistor. Connect your button between D2 and GND.
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  int lightLevel = analogRead(ldrPin);
  
  // With INPUT_PULLUP, the pin reads LOW when the button is pressed
  bool buttonPressed = (digitalRead(buttonPin) == LOW); 

  // 1. SUNRISE DETECTED
  if (lightLevel < lightThreshold && !alarmRinging && !alreadyWokeUpToday) {
    alarmRinging = true;
    Serial.println("Sunrise Detected! Alarm Ringing.");
  }

  // 2. BUTTON PRESSED (Turn off and Lockout)
  if (buttonPressed && alarmRinging) {
    alarmRinging = false;
    digitalWrite(buzzerPin, LOW); // Force buzzer off
    alreadyWokeUpToday = true;    // Lock out the alarm for the rest of the day
    Serial.println("Alarm Stopped. Locked for the day.");
    delay(500); // Small delay to prevent double-triggering the button
  }

  // 3. NIGHTTIME RESET
  if (lightLevel > darkThreshold && alreadyWokeUpToday) {
    alreadyWokeUpToday = false;   // Unlock the alarm for the next morning
    Serial.println("Nighttime Detected. System Reset for tomorrow.");
  }

  // 4. BEEPING LOGIC (Without using delay)
  if (alarmRinging) {
    unsigned long currentMillis = millis(); 
    
    // Check if 500ms have passed
    if (currentMillis - previousMillis >= beepInterval) {
      previousMillis = currentMillis; // Reset the timer
      
      // Toggle the buzzer state
      if (buzzerState == LOW) {
        buzzerState = HIGH;
      } else {
        buzzerState = LOW;
      }
      digitalWrite(buzzerPin, buzzerState); 
    }
  } else {
    // Make absolutely sure the buzzer stays off when the alarm is not ringing
    digitalWrite(buzzerPin, LOW); 
  }
}