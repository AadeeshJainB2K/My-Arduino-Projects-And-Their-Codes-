
//www.quadstore.in
//www.quadrobotics.in
//Smart Dustbin by Quad Store

#include <Servo.h>   //servo library
#include <Arduino.h>
Servo servo;     
int trigPin = 9;    
int echoPin = 8;   
int servoPin = 3;
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
