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

const int frontWall = 10;
const int leftWall = 9;
const int rightWall = 8;

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

typedef enum {
              FORWARD = 0,
              LEFT  = 1,
              RIGHT = 2,
              } TURN;

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

byte pastPosX = NULL;
byte pastPosY = NULL;

byte robotOrientation = NORTH;

byte xleft=robotX;
byte yleft=robotY;
byte xfront=robotX;
byte yfront=robotY;
byte xright=robotX;
byte yright=robotY;
byte xback=robotX;
byte yback=robotY;

bool detectNoFWall = true;
bool detectNoRWall = true;
bool detectNoLWall = true;
bool accessGranted = false;

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

byte posStack [20][2];

byte turnStack [20];

int stackIndex=0;

int rightServoMap(int angle) {
  int newAngle = 180 - angle;
  return newAngle;
}

void rightOrientation(){
  if(robotOrientation == NORTH){
    robotOrientation = EAST;
  }
  if(robotOrientation == EAST) {
    robotOrientation = SOUTH;
  }
  if(robotOrientation == SOUTH) {
    robotOrientation = WEST;
  }
  if(robotOrientation == WEST) {
    robotOrientation = NORTH;
  }
}

void leftOrientation(){
  if(robotOrientation == NORTH){
    robotOrientation = WEST;
  }
  if(robotOrientation == WEST) {
    robotOrientation = SOUTH;
  }
  if(robotOrientation == SOUTH) {
    robotOrientation = EAST;
  }
  if(robotOrientation == EAST) {
    robotOrientation = NORTH;
  }
}

void resetIndex(){
   xleft=robotX; 
   yleft=robotY;
   xfront=robotX;
   yfront=robotY;
   xright=robotX;
   yright=robotY;
   xback=robotX;
   yback=robotY;
}

bool withinMazeX(byte xCoord) {
  if(xCoord > 3 || xCoord < 0) {
    return false;
  } else {
    return true;
  } 
}

bool withinMazeY(byte yCoord) {
  if(yCoord > 4 || yCoord < 0) {
    return false;
  } else {
    return true;
  } 
}

// NOTE: MAKE XNULL AND YNULL FUNCTIONS FOR WHEN THE INDICES ARE OUT OF THE MAZE MATRIX
void neighbourIndex(){
   if(robotOrientation == NORTH){
     xleft=robotX-1;
     yleft=robotY;
     xfront=robotX;
     yfront=robotY-1;
     xright=robotX+1;
     yright=robotY;
     xback=robotX;
     yback=robotY+1;
  }
  if(robotOrientation == EAST) {
     xleft=robotX;
     yleft=robotY-1;
     xfront=robotX+1;
     yfront=robotY;
     xright=robotX;
     yright=robotY+1;
     xback=robotX-1;
     yback=robotY;
  }
  if(robotOrientation == SOUTH) {
     xleft=robotX+1;
     yleft=robotY;
     xfront=robotX;
     yfront=robotY+1;
     xright=robotX-1;
     yright=robotY;
     xback=robotX;
     yback=robotY-1;
  }
  if(robotOrientation == WEST) {
     xleft=robotX;
     yleft=robotY+1;
     xfront=robotX-1;
     yfront=robotY;
     xright=robotX;
     yright=robotY-1;
     xback=robotX+1;
     yback=robotY;
  }
}

//check
void rightTurn() {
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(300);

  while ((analogRead(outerLeftPin) < threshold) && (analogRead(outerRightPin) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  
  rightServoAngle = rightServoMap(180);
  leftServoAngle = 180;
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(200);

  rightOrientation();
  visited[yright][xright] = 6;
  visited[robotY][robotX] = 1;
  robotX = xright;
  robotY = yright;
}

void opposite() {
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(300);

  while ((analogRead(outerLeftPin) < threshold) && (analogRead(outerRightPin) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(300);
  while ((analogRead(outerLeftPin) < threshold) && (analogRead(outerRightPin) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  rightServoAngle = rightServoMap(180);
  leftServoAngle = 180;
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(200);

  rightOrientation();
  rightOrientation();
  visited[yback][xback]=6;
  visited[robotY][robotX] = 1;
  robotX = xback;
  robotY = yback;
}

void leftTurn(){
  leftServoAngle = 0;
  rightServoAngle = rightServoMap(180);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(300);

  while ((analogRead(outerLeftPin) < threshold) && (analogRead(outerRightPin) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  
  rightServoAngle = rightServoMap(180);
  leftServoAngle = 180;
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(200);
  leftOrientation();
  
  visited[yleft][xleft]=6;
  visited[robotY][robotX] = 1;
  robotX = xleft;
  robotY = yleft;
}

void lineFollow(){
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
}

void goStraight(){
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(150);
    
    visited[yfront][xfront]=6;
    visited[robotY][robotX] = 1;
    robotX = xfront;
    robotY = yfront;
}

void currentPosition() {
  for (int i =0; i<5;i++){
    for (int j=0; j<4; j++){
      if (visited[i][j]== 6){
        robotX = j;
        robotY = i;
      }
    }
  }
}

void updateCurrentPosF() {
  visited[yfront][xfront] = 6;
  
}

void updateCurrentPosR() {
  visited[yright][xright] = 6;
  visited[robotY][robotX] = 1;
}

void updateCurrentPosL() {
  visited[yleft][xleft] = 6;
  visited[robotY][robotX] = 1;
}

void lightUp(){
  // check if done with maze, aka, all have been visited
  pinMode (ledPin, HIGH);
}

byte wallOrientation() {
  byte wall = 0;
  if(robotOrientation == NORTH) {
    if(!detectNoFWall){
      wall |= NORTH;
    }
    if(!detectNoLWall){
      wall |= WEST;
    }
    if(!detectNoRWall){
      wall |= EAST;
    }  
  }
  else if(robotOrientation == EAST) {
    if(!detectNoFWall){
      wall |= EAST;
    }
    if(!detectNoLWall){
      wall |= NORTH;
    }
    if(!detectNoRWall){
      wall |= SOUTH;
    } 
  }
  else if(robotOrientation == SOUTH) {
    if(!detectNoFWall){
      wall |= SOUTH;
    }
    if(!detectNoLWall){
      wall |= EAST;
    }
    if(!detectNoRWall){
      wall |= WEST;
    } 
  }
  else if(robotOrientation == WEST) {
    if(!detectNoFWall){
      wall |= WEST;
    }
    if(!detectNoLWall){
      wall |= SOUTH;
    }
    if(!detectNoRWall){
      wall |= NORTH;
    } 
  }
  return wall;  
}

void updateWallMatrix() {
  wall[robotY][robotX] = wallOrientation();
}

/**************************************************************************/
//stack helper functions

void stack_push(byte x, byte y) {
  byte pos[2]= {x, y};
  posStack[stackIndex][0] = pos[0];
  posStack[stackIndex][1] = pos[1];
  
  //on_stack[pos] = true;
  stackIndex++;
}

// Return true if the stack is empty. Only works on the stack defined globally as int stack[50].
bool stack_empty() {
  return (stackIndex == 0);
}

bool turnStack_empty() {
  return (stackIndex == 0);
}

// Return the value on top of the stack.
int turnStack_top() {
  if (turnStack_empty()) return NULL;
  return turnStack[stackIndex-1];
}

void stack_pop() {
  if (stack_empty()) return ;
  stackIndex--;
}

/**************************************************************************/

//backtracking helper function

//helper function: pop current position, go to previous position, 
//check left and right sides for unvisited and walls (priority)
//if both are not possible, then go to previous in stack
  
void backtrack() {
  
  while (!detectNoLWall || !detectNoRWall){
    if((outerLeftVal > threshold) && (outerRightVal > threshold)){
  
      stack_pop();  
      
      if (turnStack_top==0) {
        goStraight();
      }
      else if (turnStack_top==1) {
        leftTurn();
      }
      else if (turnStack_top==2) {
        rightTurn();
      }
      neighbourIndex();   //so it'll set front back left right indexes correctly based on the robot orientation
      
      middleLeftVal = analogRead(middleLeftPin);
      middleRightVal = analogRead(middleRightPin);
      outerLeftVal = analogRead(outerLeftPin);
      outerRightVal = analogRead(outerRightPin);
      lineFollow();
              
      if (!detectNoLWall) {
        if (visited[yleft][xleft]==0){
          //go left
          //update visited to reflect new current position and set the old current position to 1
          leftTurn();
          //add to stack 
          stack_push(robotX, robotY);
          return;
        }
      }
  
      else if (!detectNoRWall) {
        if (visited[yright][xright]==0){
          //go right
          //update visited to reflect new current position and set the old current position to 1
          rightTurn();
          //add to stack 
          stack_push(robotX, robotY);
          return;
        }
      }
    }  
    currentPosition();    // so it'll set robotX and robotY to current position
    resetIndex();    //so it'll set all of x and y values of back left right forward to robot x and y 
  
  }
}

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

    
  
  // greater than 750 on the line
  // less than 750 off the line
   
  
    // intersection
    lineFollow();
    detectNoFWall = digitalRead(frontWall);
    detectNoRWall = digitalRead(rightWall);
    detectNoLWall = digitalRead(leftWall);
    if((outerLeftVal > threshold) && (outerRightVal > threshold)){
      // use wall sensors to check walls on each side 
      //translate local walls to global walls  = done
      //wallOrientation();
      //visited matrix location to find current pos = done
      //currentPosition();
      //change the wall matrix to reflect current wall changes = done 
      updateWallMatrix();
      //dfs to choose where to go next

      /***********************************************************************/
      //dfs
      //when we are at a new position (at intersection)
      //IF NEW PLACE EXISTS FROM CURRENT POSITION
      //check walls and surrounded areas' visited states


      neighbourIndex();   //so it'll set front back left right indexes correctly based on the robot orientation

      //front priority
      //check wall sensor
      if (detectNoFWall && visited[yfront][xfront] == 0 && withinMazeX(xfront) && withinMazeY(yfront)) {
        //check visited (so if unvisited go straight)        
        //go front
        //update visited to reflect new current position and set the old current position to 1
        //I changed the movement functions so that they'll update the old pos and new pos according to how they move
        goStraight();
        //add to stack
        turnStack[stackIndex] = FORWARD; 
        stack_push(robotX, robotY);
        
        
      } else if (detectNoLWall && visited[yleft][xleft] == 0 && withinMazeX(xleft) && withinMazeY(yleft)) {
        //go left
        //update visited to reflect new current position and set the old current position to 1
        leftTurn();
        //add to stack 
        turnStack[stackIndex] = RIGHT;
        stack_push(robotX, robotY);
      } else if (detectNoRWall && visited[yright][xright] == 0 && withinMazeX(xright) && withinMazeY(yright)) {
        rightTurn();
        //go right
        //update visited to reflect new current position and set the old current position to 1
        //rightTurn();
        //add to stack
        turnStack[stackIndex] = LEFT; 
        stack_push(robotX, robotY);
        
      } else {
        //turn 180 degrees
        opposite();
        //backtracking code to prevent infinite loop
        backtrack();
        //helper function: pop current position, go to previous position, 
        //check left and right sides for unvisited and walls (priority)
        //if both are not possible, then go to previous in stack
  
      }

      currentPosition();    // so it'll set robotX and robotY to current position
      resetIndex();    //so it'll set all of x and y values of back left right forward to robot x and y 


      /***********************************************************************/
         
      /*
      rightServo.write(rightServoMap(90));
      leftServo.write(90);  
      delay(100);
      */
    }
    else{
      lightUp();
    }
    
//  else{    
//    //we commented this out bc it wouldn't move    
//    //    rightServo.write(rightServoMap(90));
//    //    leftServo.write(90);  
//    //    delay(100);
//  }
}
  

