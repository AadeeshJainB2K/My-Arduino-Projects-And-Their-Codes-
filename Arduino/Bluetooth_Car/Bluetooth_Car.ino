// ---------------- MOTOR PINS (L298N) ----------------
#define ENA 3     // Left motor speed (PWM)
#define IN1 4
#define IN2 5

#define ENB 9     // Right motor speed (PWM)
#define IN3 6
#define IN4 7

// ---------------- OTHER PINS ----------------
#define buzPin 13     // Horn
#define rPin 10       // RGB Red
#define gPin 11       // RGB Green
#define bPin 12       // RGB Blue

int valSpeed = 255;
bool btConnected = false;
unsigned long lastCmdTime = 0;


// ---------------- SETUP ----------------
void setup() {

  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(buzPin, OUTPUT);
  pinMode(rPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  pinMode(bPin, OUTPUT);

  StopMotors();

  // Bluetooth NOT connected → RED
  setRGB(255, 0, 0);
}



// ---------------- MAIN LOOP ----------------
void loop() {

  if (Serial.available() > 0) {
    btConnected = true;
    lastCmdTime = millis();
    setRGB(0, 255, 0);  // Green = Connected

    char cmd = Serial.read();
    handleCommand(cmd);
  }

  // Auto disconnect if no command
  if (btConnected && (millis() - lastCmdTime > 5000)) {
    btConnected = false;
    StopMotors();
    setRGB(255, 0, 0);  // Red = Disconnected
  }
}



// ---------------- COMMAND HANDLER ----------------
void handleCommand(char cmd) {

  // Car moving → turn OFF RGB
  if (cmd=='F'||cmd=='B'||cmd=='L'||cmd=='R'||cmd=='G'||cmd=='H'||cmd=='I'||cmd=='J')
      setRGB(0,0,0);

  switch(cmd) {

    case 'F':   // Forward
      moveForward(valSpeed);
      break;

    case 'B':   // Backward
      setRGB(255,255,0); // Yellow
      moveBackward(valSpeed);
      break;

    case 'L':   // Turn left
      turnLeft(valSpeed);
      break;

    case 'R':   // Turn right
      turnRight(valSpeed);
      break;

    case 'G':   // Forward-left
      moveCustom(valSpeed/4, valSpeed);
      break;

    case 'H':   // Forward-right
      moveCustom(valSpeed, valSpeed/4);
      break;

    case 'I':   // Backward-left
      setRGB(255,255,0);
      moveCustom(-valSpeed/4, -valSpeed);
      break;

    case 'J':   // Backward-right
      setRGB(255,255,0);
      moveCustom(-valSpeed, -valSpeed/4);
      break;

    case 'S':   // Stop
      StopMotors();
      break;

    // HORN
    case 'Y': digitalWrite(buzPin, HIGH); break;  // Horn ON
    case 'y': digitalWrite(buzPin, LOW);  break;  // Horn OFF

    // HEADLIGHT
    case 'X': setRGB(255,255,255); break;  // White
    case 'x': setRGB(0,0,0); break;        // OFF

    // SPEED
    case '0': SetSpeed(0); break;
    case '1': SetSpeed(25); break;
    case '2': SetSpeed(50); break;
    case '3': SetSpeed(75); break;
    case '4': SetSpeed(100); break;
    case '5': SetSpeed(125); break;
    case '6': SetSpeed(150); break;
    case '7': SetSpeed(175); break;
    case '8': SetSpeed(200); break;
    case '9': SetSpeed(255); break;
  }
}



// ---------------- MOTOR FUNCTIONS ----------------
void SetSpeed(int s){
  valSpeed = s;
}

void moveForward(int s){
  analogWrite(ENA, s);
  analogWrite(ENB, s);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward(int s){
  analogWrite(ENA, s);
  analogWrite(ENB, s);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft(int s){
  analogWrite(ENA, s);
  analogWrite(ENB, s);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight(int s){
  analogWrite(ENA, s);
  analogWrite(ENB, s);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveCustom(int leftSpeed, int rightSpeed){

  // LEFT MOTOR
  if(leftSpeed >= 0){
    analogWrite(ENA, leftSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    analogWrite(ENA, -leftSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  // RIGHT MOTOR
  if(rightSpeed >= 0){
    analogWrite(ENB, rightSpeed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    analogWrite(ENB, -rightSpeed);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

void StopMotors(){
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}



// ---------------- RGB FUNCTION ----------------
void setRGB(int r, int g, int b){
  analogWrite(rPin, r);
  analogWrite(gPin, g);
  analogWrite(bPin, b);
}