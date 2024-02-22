
#include <Servo.h>

int chintuPin = 8;
int mintuPin = 9;

Servo chintuMotor;
Servo mintuMotor;

void setup() {
  pinMode(chintuPin, INPUT);
  pinMode(mintuPin, INPUT);

  chintuMotor.attach(7);
  mintuMotor.attach(6);  // Assuming you are using pin 6 for the second servo
}

void loop() {
  if (digitalRead(chintuPin) == LOW) {
    chintuMotor.write(0);
    mintuMotor.write(0);
  } else if (digitalRead(mintuPin) == LOW) {
    mintuMotor.write(90);
    chintuMotor.write(90);
  }
}
