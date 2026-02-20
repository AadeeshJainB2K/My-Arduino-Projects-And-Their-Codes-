#include <LCD_I2C.h>
#include <Servo.h>

// Initialize the LCD display at I2C address 0x27, 16 columns, 2 rows
LCD_I2C lcd(0x27, 16, 2); 

// Create a Servo object
Servo myServo;

// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

// Variables for distance calculations
long duration;
float distance_cm;
int total_inches;
int feet;
int inches;

void setup() {
    // Initialize serial communication for debugging via Serial Monitor
    Serial.begin(9600);

    // Initialize the LCD
    lcd.begin(); 
    lcd.backlight();
    
    // Display a welcome message
    lcd.setCursor(0, 0);
    lcd.print("Height Meter");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    delay(2000);
    lcd.clear();

    // Define pin modes for the ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Attach the servo (optional)
    myServo.attach(servoPin);
    myServo.write(90); // Center the servo
}

void loop() {
    // 1. Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // 2. Trigger the sensor
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // 3. Read the echoPin
    duration = pulseIn(echoPin, HIGH);

    // 4. Calculate distance in centimeters
    // Speed of sound wave divided by 2 (go and return)
    distance_cm = duration * 0.034 / 2.0;

    // 5. Convert cm to total inches (1 inch = 2.54 cm)
    // We use round() to ensure accurate inch grouping
    total_inches = round(distance_cm / 2.54);

    // 6. Break total inches into feet and remaining inches
    feet = total_inches / 12;      // Divide by 12 to get whole feet
    inches = total_inches % 12;    // Modulo 12 gives the leftover inches

    // 7. Display Centimeters on Top Row (with 2 decimal places)
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distance_cm, 2);     // The '2' tells the Arduino to print 2 decimal places
    lcd.print(" cm   ");           // Extra spaces to clear old characters

    // 8. Display Feet and Inches on Bottom Row
    lcd.setCursor(0, 1);
    lcd.print("Hgt:  ");
    lcd.print(feet);
    lcd.print("ft ");
    lcd.print(inches);
    lcd.print("in      ");         // Extra spaces to clear old characters

    // 9. Print to Serial Monitor for debugging
    Serial.print("Distance: ");
    Serial.print(distance_cm, 2);
    Serial.print(" cm | Height: ");
    Serial.print(feet);
    Serial.print(" ft ");
    Serial.print(inches);
    Serial.println(" in");

    // A 500ms delay makes the LCD easier to read without flickering
    delay(500);
}