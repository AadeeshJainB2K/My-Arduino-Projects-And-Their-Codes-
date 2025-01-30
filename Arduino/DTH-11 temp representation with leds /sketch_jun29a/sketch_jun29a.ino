#include <LCD_I2C.h>
#include <DHT.h>

#define DHTPIN 2     // Pin where the DHT11 data pin is connected
#define DHTTYPE DHT11

LCD_I2C lcd(0x27, 16, 2); // I2C address 0x27 for 16x2 LCD
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.begin();          // Initialize the LCD
  lcd.backlight();      // Turn on the backlight
  lcd.setCursor(0, 0);  // Set cursor to the first column, first row
  lcd.print(F("Initializing"));
  lcd.setCursor(0, 1);
  lcd.print(F("DHT11 & LCD"));

  dht.begin();          // Initialize the DHT sensor
  delay(2000);          // Allow time for sensor to stabilize

  lcd.clear();          // Clear the LCD screen
}

void loop() {
  float temperature = dht.readTemperature();  // Read temperature in Celsius
  float humidity = dht.readHumidity();        // Read humidity

  // Check if the readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print(F("Sensor Error"));
    lcd.setCursor(0, 1);
    lcd.print(F("Check DHT11"));
  } else {
    lcd.setCursor(0, 0);
    lcd.print(F("Temp: "));
    lcd.print(temperature);
    lcd.print((char)223); // Degree symbol
    lcd.print(F("C"));

    lcd.setCursor(0, 1);
    lcd.print(F("Humidity: "));
    lcd.print(humidity);
    lcd.print(F("%"));
  }

  delay(0); // Update immediately
}
