// Define LDR pin
const int ldrPin = 2; // Assuming LDR is connected to digital pin 2

// Define LED pin
const int ledPin = 13;

// Variables to store time

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);

  // Set LDR pin as input
  pinMode(ldrPin, INPUT);
}

void loop() {
  // Read the LDR value
  int ldrValue = digitalRead(ldrPin);

  // Print the LDR value to the serial monitor
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Check if it's dark (LDR value is high)
  if (ldrValue == HIGH) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("It's dark. Turning on the street light.");
  } else {
    // Turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("It's bright. Turning off the street light.");
  }

}
