
#include <SPI.h>
#include <Wire.h>
#include <Servo.h>   //servo library
int trigPin = 9;    
int echoPin = 8;   
int servoPin = 5;
int led= 10;
long duration, dist, average;   
long aver[3];   //array for average


void setup() {       
    Serial.begin(9600);
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    servo.write(0);         //close cap on power on
    delay(100);
    servo.detach(); 
} 

void measure() {  
digitalWrite(10,HIGH);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}
void loop() { 
  for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    

if ( dist<200 ) {
//Change distance as per your need
 servo.attach(servoPin);
 delay(1);
 servo.write(350);  
 delay(3000);       
 servo.write(0);    
 delay(1000);
 servo.detach();      
}
Serial.print(dist);
}


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
