#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf;

#define BUTTON_PIN 4      // RF trigger button
#define BUZZER_PIN 9      // Optional buzzer on remote for feedback

void setup() {
  Serial.begin(9600);
  rf.init();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("RF Remote Ready");
}

void loop() {
  static unsigned long lastSendTime = 0;
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect button press (active LOW)
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastSendTime > 1000) {
    const char *msg = "START";
    rf.send((uint8_t *)msg, strlen(msg));
    rf.waitPacketSent();

    Serial.println("RF: START sent");
    tone(BUZZER_PIN, 1000, 150);   // short feedback beep
    lastSendTime = millis();
  }

  lastButtonState = buttonState;
}