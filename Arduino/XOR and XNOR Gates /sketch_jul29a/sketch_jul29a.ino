// Define input pins for XOR
const int btnXOR1 = 5;
const int btnXOR2 = 4;

// Define input pins for XNOR
const int btnXNOR1 = 2;
const int btnXNOR2 = 3;

// Define output pins for LEDs
const int ledXOR = 6;
const int ledXNOR = 7;

void setup() {
  // Set button pins as INPUT_PULLUP (assuming push buttons are active LOW)
  pinMode(btnXOR1, INPUT_PULLUP);
  pinMode(btnXOR2, INPUT_PULLUP);
  pinMode(btnXNOR1, INPUT_PULLUP);
  pinMode(btnXNOR2, INPUT_PULLUP);

  // Set LED pins as OUTPUT
  pinMode(ledXOR, OUTPUT);
  pinMode(ledXNOR, OUTPUT);
}

void loop() {
  // Read button states and invert because buttons are active LOW
  bool a = !digitalRead(btnXOR1);
  bool b = !digitalRead(btnXOR2);
  bool c = !digitalRead(btnXNOR1);
  bool d = !digitalRead(btnXNOR2);

  // XOR operation: a XOR b
  bool xorResult = a ^ b;

  // XNOR operation: c XNOR d → NOT(c XOR d)
  bool xnorResult = !(c ^ d);

  // Display outputs on LEDs
  digitalWrite(ledXOR, xorResult);
  digitalWrite(ledXNOR, xnorResult);

  delay(0); // small delay to stabilize input reading
}
