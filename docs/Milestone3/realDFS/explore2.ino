/* 
 *    Maze mapping Robot
 *  
 *  
 *  
 *  
 *  
 */

#include <Servo.h>

// Pin Assignments
const int rightServoPin = 6;
const int leftServoPin = 5;

const int middleRightPin = A0;
const int middleLeftPin = A1;
const int outerRightPin = A2;
const int outerLeftPin = A3;

const int ledPin = 13;

const int frontWall = 8;
const int leftWall = 9;
const int rightWall = 10;

Servo rightServo;
Servo leftServo; 

// Constants
#define WALL_NORTH  1 // 0001
#define WALL_EAST   2 // 0010
#define WALL_SOUTH  4 // 0100
#define WALL_WEST   8 // 1000

const int threshold = 800; 

const int delayTime = 2;

typedef enum {
              NORTH = 1,
              EAST  = 2,
              SOUTH = 4,
              WEST  = 8
              } ORIENTATION;

// Global Variables
int leftServoAngle = 90;
int rightServoAngle = 90;

int middleLeftVal = 0;
int middleRightVal = 0;
int outerLeftVal = 0;
int outerRightVal = 0;

int visitedBox = 0;

byte robotX = 3;
byte robotY = 4;
byte robotOrientation = NORTH;

byte xleft=robotX;
byte yleft=robotY;
byte xfront=robotX;
byte yfront=robotY;
byte xright=robotX;
byte yright=robotY;
byte xback=robotX;
byte yback=robotY;

bool detectFWall = true;
bool detectRWall = true;
bool detectLWall = true;

byte visited[5][4] =  {{0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,0},
                       {0,0,0,6}};
                  
byte wall[5][4] = {{9,1,1,3},
                   {8,0,0,2},
                   {8,0,0,2},
                   {8,0,0,2},
                   {12,4,4,6}};

void setup() {
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);

  leftServoAngle = 90;
  rightServoAngle = rightServoMap(90);

  pinMode(frontWall, INPUT);
  pinMode(rightWall, INPUT);
  pinMode(leftWall, INPUT);
  pinMode(ledPin, OUTPUT);

  rightServo.write(rightServoAngle);
  leftServo.write(leftServoAngle);
  delay(2000); //Wait 2 seconds
}

void loop() {  
  middleLeftVal = analogRead(middleLeftPin);
  middleRightVal = analogRead(middleRightPin);
  outerLeftVal = analogRead(outerLeftPin);
  outerRightVal = analogRead(outerRightPin);

  detectFWall = digitalRead(frontWall);
  detectRWall = digitalRead(rightWall);
  detectLWall = digitalRead(leftWall);  
  
  // greater than 750 on the line
  // less than 750 off the line
   
  if(!detectFWall){
    if ((middleLeftVal > threshold) && (middleRightVal < threshold)) {
        rightServoAngle = rightServoMap(180);
        leftServoAngle = 95;
        rightServo.write(rightServoAngle);
        leftServo.write(leftServoAngle);
        delay(delayTime);
      }
  
      if ((middleLeftVal < threshold) && (middleRightVal > threshold)) {
        rightServoAngle = rightServoMap(95);
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

      // use wall sensors to check walls on each side 
      //translate local walls to global walls  = done
      wallOrientation();
      //visited matrix location to find current pos = done
      currentPosition();
      //change the wall matrix to reflect current wall changes = done 
      updateWallMatrix()
      //dfs to choose where to go next

/***********************************************************************/
//dfs
//when we are at a new position (at intersection)
//IF NEW PLACE EXISTS FROM CURRENT POSITION
//check walls and surrounded areas' visited states


indexstuff();   //so it'll set front back left right indexes correctly based on the robot orientation

//front priority
//check wall sensor
if (!detectFwall) {
  //check visited (so if unvisited go straight)
  if (visited[xfront][yfront]==0){
    //go front
    //update visited to reflect new current position and set the old current position to 1
    //I changed the movement functions so that they'll update the old pos and new pos according to how they move
    goStraight();
    //add to stack 
    
  }
}
else (!detectLwall) {
  if (visited[xleft][yleft]==0){
    //go left
    //update visited to reflect new current position and set the old current position to 1
    leftturn();
    //add to stack 
  }
}

else (!detectRwall) {
  if (visited[xright][yright]==0){
    //go right
    //update visited to reflect new current position and set the old current position to 1
    rightturn();
    //add to stack 
  }
}
else {
  opposite();
  }

currentPosition();    // so it'llset robotX and robotY to current position
resetindexstuff();    //so it'll set all of x and y values of back left right forward to robot x and y 


/***********************************************************************/

      //change and update visited matrix DON'T FORGET TO IMPLEMENT NEW POSITION STUFF
      updateVisited();


      if (visitedBox==20){
      // check if done with maze, aka, all have been visited
            rightServo.write(rightServoMap(90));
            leftServo.write(90);  
            delay(100);
            pinMode (ledPin, HIGH);
        }
      
      /*
      rightServo.write(rightServoMap(90));
      leftServo.write(90);  
      delay(100);
      */
    }
  } 
  else
  {    
    rightServo.write(rightServoMap(90));
    leftServo.write(90);  
    delay(100);
  }
  
      
  
}
