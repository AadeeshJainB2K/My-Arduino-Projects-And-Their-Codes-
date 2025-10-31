/*
  Diwani Rocket Launcher – Final Stable Version
  - Arduino UNO
  - Relays (Active LOW) -> 10, 11
  - Buzzer -> 9
  - RF Receiver Input -> 3 (remote start)
  - Switches (INPUT_PULLUP, active LOW):
      RESET   -> 7
      INC     -> 6
      DEC     -> 5
      START   -> 4
  - LCD I2C (0x27) on A4 (SDA), A5 (SCL)
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ===== Pins =====
const uint8_t RELAY1_PIN = 10;
const uint8_t RELAY2_PIN = 11;
const uint8_t BUZZER_PIN = 9;
const uint8_t RF_PIN     = 3;

const uint8_t SW_RESET_PIN = 7;
const uint8_t SW_INC_PIN   = 6;
const uint8_t SW_DEC_PIN   = 5;
const uint8_t SW_START_PIN = 4;

// ===== Constants =====
const unsigned long RELAY_HOLD_MS = 5000UL;
const unsigned long TIMER_MAX_SECONDS = 3600UL;
const unsigned long DEBOUNCE_MS = 150;   // a little longer = more stable

const unsigned int BUZZER_BEEP_MS = 120;
const unsigned int BUZZER_FINAL_MS = 1000;

// ===== LCD =====
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== State =====
volatile bool rfStartRequest = false;
unsigned long remainingSeconds = 0;
bool running = false;
bool relaysActive = false;

// last press times
unsigned long lastBtnReset = 0;
unsigned long lastBtnInc   = 0;
unsigned long lastBtnDec   = 0;
unsigned long lastBtnStart = 0;

// track last state to avoid repeats while held
bool prevResetState = HIGH;
bool prevIncState   = HIGH;
bool prevDecState   = HIGH;
bool prevStartState = HIGH;

// tick
unsigned long lastTick = 0;

// ===== Helper =====
inline bool isPressed(uint8_t pin) { return digitalRead(pin) == LOW; }

void rfPulse() { rfStartRequest = true; }

void shortBeep() {
  tone(BUZZER_PIN, 2000);
  delay(BUZZER_BEEP_MS);
  noTone(BUZZER_PIN);
}

void finalBeep() {
  tone(BUZZER_PIN, 1500);
  delay(BUZZER_FINAL_MS);
  noTone(BUZZER_PIN);
}

// ===== Setup =====
void setupPins() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  pinMode(SW_RESET_PIN, INPUT_PULLUP);
  pinMode(SW_INC_PIN,   INPUT_PULLUP);
  pinMode(SW_DEC_PIN,   INPUT_PULLUP);
  pinMode(SW_START_PIN, INPUT_PULLUP);

  pinMode(RF_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RF_PIN), rfPulse, FALLING);
}

void setup() {
  Serial.begin(115200);
  setupPins();

  lcd.init();
  lcd.backlight();

  remainingSeconds = 0;
  running = false;
  relaysActive = false;
  lastTick = millis();
  updateLCD();
  Serial.println("System Ready.");
}

// ===== LCD =====
void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Timer: ");
  unsigned long s = remainingSeconds;
  unsigned int mins = s / 60;
  unsigned int secs = s % 60;
  char buf[6];
  sprintf(buf, "%02u:%02u", mins, secs);
  lcd.print(buf);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  if (relaysActive) lcd.print("STATUS: FIRE     ");
  else if (running) lcd.print("STATUS: RUNNING  ");
  else if (remainingSeconds == 0) lcd.print("STATUS: ZERO-LOCK");
  else lcd.print("STATUS: STOPPED  ");
}

// ===== Timer Adjust =====
void increaseTimerPerPress() {
  unsigned long before = remainingSeconds;
  if (remainingSeconds < 60) remainingSeconds += 5;
  else remainingSeconds += 30;
  if (remainingSeconds > TIMER_MAX_SECONDS) remainingSeconds = TIMER_MAX_SECONDS;
  Serial.print("Increase: "); Serial.print(before); Serial.print(" -> "); Serial.println(remainingSeconds);
  updateLCD();
}

void decreaseTimerPerPress() {
  unsigned long before = remainingSeconds;
  if (remainingSeconds == 0) return;

  if (remainingSeconds <= 60) {
    if (remainingSeconds <= 5) remainingSeconds = 0;
    else remainingSeconds -= 5;
  } else {
    if (remainingSeconds <= 30) remainingSeconds = 0;
    else remainingSeconds -= 30;
  }
  Serial.print("Decrease: "); Serial.print(before); Serial.print(" -> "); Serial.println(remainingSeconds);
  updateLCD();
}

// ===== Relay Control =====
void activateRelays() {
  if (relaysActive) return;
  Serial.println("Activating relays...");
  relaysActive = true;

  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);
  updateLCD();
  finalBeep();

  delay(RELAY_HOLD_MS);

  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
  relaysActive = false;
  Serial.println("Relays released.");
  updateLCD();
}

// ===== Buttons =====
void handleButtons() {
  unsigned long now = millis();

  // RESET
  bool resetNow = isPressed(SW_RESET_PIN);
  if (resetNow != prevResetState && resetNow == LOW && now - lastBtnReset > DEBOUNCE_MS) {
    lastBtnReset = now;
    running = false;
    remainingSeconds = 0;
    Serial.println("RESET -> Timer reset to 0");
    updateLCD();
  }
  prevResetState = resetNow;

  // INCREASE
  bool incNow = isPressed(SW_INC_PIN);
  if (incNow != prevIncState && incNow == LOW && now - lastBtnInc > DEBOUNCE_MS) {
    lastBtnInc = now;
    increaseTimerPerPress();
  }
  prevIncState = incNow;

  // DECREASE
  bool decNow = isPressed(SW_DEC_PIN);
  if (decNow != prevDecState && decNow == LOW && now - lastBtnDec > DEBOUNCE_MS) {
    lastBtnDec = now;
    decreaseTimerPerPress();
  }
  prevDecState = decNow;

  // START (toggle start/stop)
  bool startNow = isPressed(SW_START_PIN);
  if (startNow != prevStartState && startNow == LOW && now - lastBtnStart > DEBOUNCE_MS) {
    lastBtnStart = now;

    if (remainingSeconds == 0) {
      Serial.println("START blocked: timer = 0");
      tone(BUZZER_PIN, 1000);
      delay(120);
      noTone(BUZZER_PIN);
    } else {
      running = !running;
      if (running) {
        lastTick = now;
        Serial.println("Countdown STARTED");
        shortBeep();
      } else {
        Serial.println("Countdown PAUSED");
        tone(BUZZER_PIN, 800);
        delay(120);
        noTone(BUZZER_PIN);
      }
      updateLCD();
    }
  }
  prevStartState = startNow;
}

// ===== RF =====
void processRF() {
  if (!rfStartRequest) return;
  rfStartRequest = false;
  Serial.println("RF start received.");
  if (remainingSeconds == 0) {
    Serial.println("RF start blocked (0s).");
    tone(BUZZER_PIN, 1200);
    delay(120);
    noTone(BUZZER_PIN);
    return;
  }
  running = !running;
  lastTick = millis();
  updateLCD();
}

// ===== Countdown =====
void handleCountdownTick() {
  if (!running) return;
  unsigned long now = millis();
  if (now - lastTick >= 1000UL) {
    unsigned long elapsed = (now - lastTick) / 1000UL;
    lastTick += elapsed * 1000UL;

    if (remainingSeconds <= elapsed) remainingSeconds = 0;
    else remainingSeconds -= elapsed;

    updateLCD();

    if (remainingSeconds > 0 && remainingSeconds <= 5) shortBeep();

    if (remainingSeconds == 0 && running) {
      running = false;
      Serial.println("Countdown done -> FIRE!");
      updateLCD();
      activateRelays();
    }
  }
}

// ===== Main Loop =====
void loop() {
  handleButtons();
  processRF();
  handleCountdownTick();
  delay(10);
}