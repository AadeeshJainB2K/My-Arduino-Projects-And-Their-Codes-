
#include <SPI.h>
#include <Wire.h>

#define trigPin 9
#define echoPin 8
#define relayPin 10

void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(relayPin, OUTPUT);
}

void loop() {
float duration;
float distance_cm;
float distance_in;

digitalWrite(trigPin, LOW); //PULSE __|---|__
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance_cm = (duration/2) / 29.1;
distance_in = (duration/2) / 73.914;

if (distance_cm<100){
  digitalWrite(relayPin, HIGH);
}else{
  digitalWrite(relayPin, LOW);
}

Serial.println(distance_cm);
Serial.println(distance_in);
}