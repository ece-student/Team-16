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

const int ledPin = 13;

const int threshold = 800; 

const int delayTime = 4;

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

void rightturn() {
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(10);

  while ((analogRead(outerLeftVal) < threshold) && (analogRead(outerRightVal) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  intersection += 1;
}

void leftturn(){
  leftServoAngle = 0;
  rightServoAngle = rightServoMap(180);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(100);

  while ((analogRead(outerLeftVal) < threshold) && (analogRead(outerRightVal) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  intersection += 1;
}

void setup() {
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);
  delay(2000); //Wait 2 seconds
  //Serial.begin(9600);

  leftServoAngle = 90;
  rightServoAngle = rightServoMap(90);

  pinMode(ledPin, OUTPUT);

  rightServo.write(rightServoAngle);
  leftServo.write(leftServoAngle);
  delay(10);
}

void loop() {
  /*Serial.print("outer Left "); 
  Serial.print(analogRead(outerLeftPin));
  Serial.print("outer Right ");
  Serial.print(analogRead(outerRightPin));
  Serial.print("middle Left ");
  Serial.print(analogRead(middleLeftPin));
  Serial.print("middle Right ");
  Serial.println(analogRead(middleRightPin));*/
  
  middleLeftVal = analogRead(middleLeftPin);
  middleRightVal = analogRead(middleRightPin);
  outerLeftVal = analogRead(outerLeftPin);
  outerRightVal = analogRead(outerRightPin);

  // greater than 750 on the line
  // less than 750 off the line
  if ((middleLeftVal > threshold) && (middleRightVal < threshold)) {
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 98;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(delayTime);
  }

  if ((middleLeftVal < threshold) && (middleRightVal > threshold)) {
    rightServoAngle = rightServoMap(98);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(delayTime);
  }

  if ((middleLeftVal > threshold) && (middleRightVal > threshold)) {
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(delayTime);
  }

// intersection
  if((outerLeftVal > threshold) && (outerRightVal > threshold)){
    if (intersection > 7) {
      intersection = 0;
    }
    //digitalWrite(ledPin, HIGH);
    /*rightServoAngle = rightServoMap(90);
    leftServoAngle = 90;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    */
    //delay(1000);
    
    int currTurn = turns[intersection];
    if(currTurn == 0){
      intersection += 1;
    } //straight
    if(currTurn == 1){
      leftturn();
    }
    if(currTurn == 2){
      rightturn();
    }
    digitalWrite(ledPin, LOW);
  }
}
