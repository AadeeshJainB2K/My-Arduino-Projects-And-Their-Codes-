#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_Sensor.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define GreenLed 3
#define YellowLed 4
#define RedLed 5
#define WhiteLed 6


DHT dht (DHTPIN, DHTTYPE);

int HighTemp = 25;
int LowTemp = 16;

void setup() {
// put your setup code here, to run once:
pinMode(GreenLed, OUTPUT);
pinMode(RedLed, OUTPUT);

Serial.begin(9600);
Serial.println("Temp Sensor V1.0");

dht.begin();
}

void loop() {
// put your main code here, to run repeatedly:
delay(1000);

float humidity = dht.readHumidity();
float temp = dht.readTemperature();

if (isnan(humidity) || isnan (temp)) {
Serial.println("No DHT Sensor!");
return;
}

Serial.print("Humidity: ");
Serial.print(humidity);
Serial.print("% Temperature: ");
Serial.print(temp);
Serial.println("°C");

if (temp > HighTemp && temp < LowTemp) {
digitalWrite(YellowLed, HIGH);
digitalWrite(GreenLed, LOW);
}
else ( {
digitalWrite(GreenLed, HIGH);
digitalWrite(YellowLed, LOW);
}
);}