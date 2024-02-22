const int ledPin = 11;

const int buzzerPin = 12;

const int ldrPin = A0;

void setup () {

Serial.begin(9600);

pinMode(ledPin, OUTPUT);

pinMode(buzzerPin, OUTPUT);

pinMode(ldrPin, INPUT);

}

void loop() {

int ldrStatus = analogRead(ldrPin);

if (ldrStatus <= 20) {

tone(buzzerPin, 1000000);

digitalWrite(ledPin, HIGH);

delay(100);

noTone(buzzerPin);

digitalWrite(ledPin, LOW);

delay(100);

Serial.println("----------- ALARM ACTIVATED -----------");

}

else {

noTone(buzzerPin);

digitalWrite(ledPin, LOW);

Serial.println("ALARM DEACTIVATED");

}

}