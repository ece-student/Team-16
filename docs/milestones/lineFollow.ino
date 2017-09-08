/* 
 *    Line Following Robot
 *  
 *  
 *  
 *  
 *  
 */

#include <Servo.h>

//This array tells the robot when to turn at each
//intersection given a start location. A 0 means
//keep going forward at an intersection. A 1 means
//turn left at an intersection. A 2 means turn right
//at an intersection.
int turns[] = {0,2,2,2,0,1,1,1};
int intersection = 0;

Servo rightServo;
Servo leftServo;
 
const int rightServoPin = 6;
const int leftServoPin = 5;

const int middleRightPin = A0;
const int middleLeftPin = A1;
const int outerRightPin = A2;
const int outerLeftPin = A3;

int leftServoAngle = 90;
int rightServoAngle = 90;

int middleLeftVal = 0;
int middleRightVal = 0;
int outerLeftVal = 0;
int outerRightVal = 0;

int rightServoMap(int angle) {
  int newAngle = 180 - angle;
  return newAngle;
}
/*
void forward() {
  
}*/

void setup() {
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);
  delay(2000); //Wait 2 seconds
  Serial.begin(9600);

  leftServoAngle = 180;
  rightServoAngle = rightServoMap(180);

  rightServo.write(rightServoAngle);
  leftServo.write(leftServoAngle);
  delay(10);
}

void loop() {
  Serial.println(analogRead(middleLeftPin));
  middleLeftVal = analogRead(middleLeftPin);
  middleRightVal = analogRead(middleRightPin);
  
    
  // greater than 750 on the line
  // less than 750 off the line
  if (middleLeftVal > 750 && middleRightVal < 750) {
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 98;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(1);
  }
  if (middleLeftVal < 750 && middleRightVal > 750) {
    rightServoAngle = rightServoMap(98);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(1);
  }
  if (middleLeftVal > 750 && middleRightVal > 750) {
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(1);
  }
  
}
