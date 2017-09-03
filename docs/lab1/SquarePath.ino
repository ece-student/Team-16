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

int rightServoAngle = 90;
int leftServoAngle = 90;

void setup() {
  rightMotor.attach(leftServoMotor);
  leftMotor.attach(rightServoMotor);

  rightServoAngle = 180;
  leftServoAngle = 0;
  
  rightMotor.write(rightServoAngle);
  leftMotor.write(leftServoAngle);

  delay(500);
}

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
