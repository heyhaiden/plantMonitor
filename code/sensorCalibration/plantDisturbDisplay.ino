
// include code from other folders:
#include "pingUltrasonic.h"

// define pins for ultrasonic and buzzer
const int trigPin = 9;
const int echoPin = 10;
const int buzzPin = 6;

// setting Disturb mode to False
boolean disturb_mode = false;

int distance; // variable for the distance measurement
long duration; // variable for duration of time

void setup() {

  // boot up Ultrasonic sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzPin, OUTPUT);

  // start serial communication
  Serial.begin(9600); // 
  Serial.println("Ultrasonic Sensor + Buzzer Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");

  delay (5000);

}

void loop() {
  
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // To check whether someone has tripped the alarm
  if (distance <= 20 && distance >= 0) {
    digitalWrite(buzzPin, HIGH);
  } else {
    digitalWrite(buzzPin, LOW);
  }
  
  delay(50);


}
  
  
  
 

