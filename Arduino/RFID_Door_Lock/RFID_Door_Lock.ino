#include <SPI.h> 
#include <RFID.h>
#include <Servo.h> 

RFID rfid(10, 9);       // D10: pin of tag reader SDA. D9: pin of tag reader RST 
unsigned char status; 
unsigned char str[MAX_LEN]; // MAX_LEN is 16: size of the array 

String accessGranted[2] = {"637241402", "15922114122"};  // RFID serial numbers to grant access to
int accessGrantedSize = 2;                                // The number of serial numbers

Servo lockServo;                // Servo for locking mechanism
int lockPos = 0;               // Locked position limit
int unlockPos = 100;             // Unlocked position limit
boolean locked = true;

int redLEDPin = 5;
int greenLEDPin = 6;

unsigned long unlockTime = 0;   // Time when the door was unlocked
const unsigned long LOCK_DURATION = 5000;  // Lock duration in milliseconds (5 seconds)

void setup() 
{ 
  Serial.begin(9600);     // Serial monitor for debugging
  Serial.println("Initializing...");
  
  SPI.begin();            // Start SPI communication with reader
  rfid.init();            // Initialization 
  pinMode(redLEDPin, OUTPUT);     // LED startup sequence
  pinMode(greenLEDPin, OUTPUT);
  digitalWrite(redLEDPin, HIGH);
  delay(200);
  digitalWrite(greenLEDPin, HIGH);
  delay(200);
  digitalWrite(redLEDPin, LOW);
  delay(200);
  digitalWrite(greenLEDPin, LOW);
  lockServo.attach(3);
  lockServo.write(lockPos);         // Move servo into locked position
  Serial.println("Place card/tag near reader...");
} 

void loop() 
{ 
  if (rfid.findCard(PICC_REQIDL, str) == MI_OK)   // Wait for a tag to be placed near the reader
  { 
    Serial.println("Card found"); 
    String temp = "";                             // Temporary variable to store the read RFID number
    if (rfid.anticoll(str) == MI_OK)              // Anti-collision detection, read tag serial number 
    { 
      Serial.print("The card's ID number is : "); 
      for (int i = 0; i < 4; i++)                 // Record and display the tag serial number 
      { 
        temp = temp + (0x0F & (str[i] >> 4)); 
        temp = temp + (0x0F & str[i]); 
      } 
      Serial.println(temp);
      checkAccess(temp);     // Check if the identified tag is allowed to open the lock
    } 
    rfid.selectTag(str); // Lock card to prevent a redundant read, removing the line will make the sketch read cards continually
  }
  
  if (locked == false && millis() - unlockTime >= LOCK_DURATION) {
    // Lock the door after the specified duration
    lockServo.write(lockPos);
    locked = true;
    Serial.println("Locking automatically...");
    digitalWrite(greenLEDPin, LOW);
  }
  
  rfid.halt();
}

void checkAccess(String temp)    // Function to check if an identified tag is registered to allow access
{
  boolean granted = false;
  for (int i = 0; i <= (accessGrantedSize - 1); i++)    // Runs through all tag ID numbers registered in the array
  {
    if (accessGranted[i] == temp)            // If a tag is found then open/close the lock
    {
      Serial.println("Access Granted");
      granted = true;
      if (locked == true)         // If the lock is closed then open it
      {
          lockServo.write(unlockPos);
          locked = false;
          unlockTime = millis();  // Record the time when the door was unlocked
          Serial.println("Unlocking...");
          digitalWrite(greenLEDPin, HIGH);    // Green LED sequence
          delay(200);
          digitalWrite(greenLEDPin, LOW);
          delay(200);
          digitalWrite(greenLEDPin, HIGH);
          delay(200);
          digitalWrite(greenLEDPin, LOW);
          delay(200);
      }
    }
  }
  if (!granted)     // If the tag is not found
  {
    Serial.println("Access Denied");
    digitalWrite(redLEDPin, HIGH);      // Red LED sequence
    delay(200);
    digitalWrite(redLEDPin, LOW);
    delay(200);
    digitalWrite(redLEDPin, HIGH);
    delay(200);
    digitalWrite(redLEDPin, LOW);
    delay(200);
  }
}
