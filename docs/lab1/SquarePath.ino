/* 
*     Square path
*
*
*
*
*/

#include <Servo.h>

Servo rightMotor;
Servo leftMotor;

const int leftServoMotor = 5;
const int rightServoMotor = 6;

int rightServoAngle = 90; // stop
int leftServoAngle = 90;

void setup() {
  rightMotor.attach(leftServoMotor);
  leftMotor.attach(rightServoMotor);

  //The robot moves forward to the side of the square
  rightServoAngle = 180;
  leftServoAngle = 0;
  
  rightMotor.write(rightServoAngle);
  leftMotor.write(leftServoAngle);

  delay(1000);

  //The robot turns left onto the side of the square
  rightServoAngle = 0;
  leftServoAngle = 0;

  delay(600);

  //The robot completes its exit from the center of the square
  rightServoAngle = 180;
  leftServoAngle = 0;
  
  rightMotor.write(rightServoAngle);
  leftMotor.write(leftServoAngle);

  delay(1000);
}


//This loop is the path for the robot to continuously travel around the square
void loop() {
  rightServoAngle = 0;
  leftServoAngle = 0;

  rightMotor.write(rightServoAngle);
  leftMotor.write(leftServoAngle);

  delay(600);

  rightServoAngle = 180;
  leftServoAngle = 0;

  rightMotor.write(rightServoAngle);
  leftMotor.write(leftServoAngle);

  delay(2000);
}
