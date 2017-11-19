/* 
 *    Maze mapping Robot
 *  
 *  
 *  
 *  
 *  
 */

#include <Servo.h>


/**************************************************************************************Pin assignments*/
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

const int threshold = 900; 

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

/*************************************************************************************Global variables*/
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
bool doOpposite    = true;

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

byte cardinalStack [20];

int stackIndex=0;

int rightServoMap(int angle) {
  int newAngle = 180 - angle;
  return newAngle;
}

void rightOrientation(){
  if(robotOrientation == NORTH){
    robotOrientation = EAST;
  }
  else if(robotOrientation == EAST) {
    robotOrientation = SOUTH;
  }
  else if(robotOrientation == SOUTH) {
    robotOrientation = WEST;
  }
  else if(robotOrientation == WEST) {
    robotOrientation = NORTH;
  }
}

void leftOrientation(){
  if(robotOrientation == NORTH){
    robotOrientation = WEST;
  }
  else if(robotOrientation == WEST) {
    robotOrientation = SOUTH;
  }
  else if(robotOrientation == SOUTH) {
    robotOrientation = EAST;
  }
  else if(robotOrientation == EAST) {
    robotOrientation = NORTH;
  }
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

//OK
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


/***********************************************************************************Movement functions*/

//Need to verify when to update robot current position
void rightTurn() {
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(400);

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

//Need to verify when to update robot current position
void opposite() {
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(400);
  while ((analogRead(outerLeftPin) < threshold) && (analogRead(outerRightPin) < threshold)){
    leftServo.write(leftServoAngle);
    rightServo.write(rightServoAngle);
    delay(delayTime);
  }
  leftServoAngle = 180;
  rightServoAngle = rightServoMap(0);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(400);
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
  visited[yback][xback] = 6;
  visited[robotY][robotX] = 1;
  robotX = xback;
  robotY = yback;
}

//Need to verify when to update robot current position 
void leftTurn(){
  leftServoAngle = 0;
  rightServoAngle = rightServoMap(180);
  leftServo.write(leftServoAngle);
  rightServo.write(rightServoAngle);
  delay(400);
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
  
  visited[yleft][xleft] = 6;
  visited[robotY][robotX] = 1;
  robotX = xleft;
  robotY = yleft;
}

//OK
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

//Need  to verify when to update robot current position
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

void stop(){
    rightServo.write(rightServoMap(90));
    leftServo.write(90);  
    delay(100);
}

//OK
/*********************************************************************************************Light up*/
void lightUp(){
  // check if done with maze, aka, all have been visited
  pinMode (ledPin, HIGH);
}

//OK
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

//Need to check where to place this function
void updateWallMatrix() {
  wall[robotY][robotX] = wallOrientation();

}
/**************************************************************************************Stack functions*/
//stack helper functions

//OK
void stack_push(byte x, byte y) {
  posStack[stackIndex][0] = x;
  posStack[stackIndex][1] = y;
  stackIndex++;
}


//OK
// Return true if the stack is empty. Only works on the stack defined globally as int stack[50].

//problematic because when you add to turnstack, won't have same index, must also pop turnstack separately
bool stack_empty() {
  return (stackIndex == 0);
}


//OK
bool turnStack_empty() {
  return (stackIndex == 0);
}

// Return the value on top of the stack.
//Need to verify
int turnStack_top() {
  if (turnStack_empty()) return NULL;
  return turnStack[stackIndex];
}

//OK
void stack_pop() {
  if (stack_empty()) return ;
  stackIndex--;
}

void cardinalStackLeftTurn(){
  if (robotOrientation==NORTH){
    cardinalStack[stackIndex]=EAST;
  }
  if (robotOrientation==SOUTH){
    cardinalStack[stackIndex]=WEST;
  }
  if (robotOrientation==EAST){
    cardinalStack[stackIndex]=SOUTH;
  }
  if (robotOrientation==WEST){
    cardinalStack[stackIndex]=NORTH;
  }
  return;
}


void cardinalStackRightTurn(){
  
  if (robotOrientation==NORTH){
    cardinalStack[stackIndex]=WEST;
  }
  if (robotOrientation==SOUTH){
    cardinalStack[stackIndex]=EAST;
  }
  if (robotOrientation==EAST){
    cardinalStack[stackIndex]=NORTH;
  }
  if (robotOrientation==WEST){
    cardinalStack[stackIndex]=SOUTH;
  }
  return;
}

void cardinalStackStraight(){
  if (robotOrientation==NORTH){
    cardinalStack[stackIndex]=SOUTH;
  }
  if (robotOrientation==SOUTH){
    cardinalStack[stackIndex]=NORTH;
  }
  if (robotOrientation==EAST){
    cardinalStack[stackIndex]=WEST;
  }
  if (robotOrientation==WEST){
    cardinalStack[stackIndex]=EAST;
  }
  return;
}


/********************************************************************************************Backtrack*/

//helper function: pop current position, go to previous position, 
//check left and right sides for unvisited and walls (priority)
//if both are not possible, then go to previous in stack
//Needs work as a whole  


/*
 * backtrack() puts the robot in the last previous position 
 * from its stack that has an accessible, unvisited position to go to.
 */
void backtrack(){
  
  //while there is not unvisited neighbor 
  while ((!detectNoLWall || visited[yleft][xleft]==1) && (!detectNoRWall || visited[yright][xright]==1) 
  && (!detectNoFWall || visited[yfront][xfront]==1) && stackIndex!=0){
    
    //at an intersection, read the current orientation and the orientation of the next on, 
    stack_pop();
//maybe have a variable for the current and old and then use the helper function based on those?
//here implement the new stuff

  //from those determine how to turn
  //turn in that direction
  }
  // else, it'll go to unvisited 

  }
}

void oldbacktrack() {
  //while there is not unvisited neighbor 
  
  //at an intersection, read the current orientation and the orientation of the next on, 
  //from those determine how to turn
  //turn in that direction
  // else, it'll go to unvisited 
    doOpposite=false;
    Serial.println("we're using backtrack");
    if((outerLeftVal > threshold) && (outerRightVal > threshold)){
      
      stack_pop();
      for (int i=0; i<20; i++){
        for (int j=0; j<2; j++){
          Serial.print(posStack[i][j]);
        }
      }
    
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
      if (detectNoFWall && visited[yfront][xfront]==0) {
          //go straight
          //update visited to reflect new current position and set the old current position to 1
          goStraight();
          //add to stack 
          stack_push(robotX, robotY);
          doOpposite=true;
          return;
        }
          
      else if (detectNoLWall && visited[yleft][xleft]==0) {
          //go left
          //update visited to reflect new current position and set the old current position to 1
          leftTurn();
          //add to stack 
          stack_push(robotX, robotY);
          doOpposite=true;
          return;
        }
      
 
      else if (detectNoRWall && visited[yright][xright]==0) {
      
          //go right
          //update visited to reflect new current position and set the old current position to 1
          rightTurn();
          //add to stack 
          stack_push(robotX, robotY);
          doOpposite=true;
          return;
        
      }

  }
}


/*******************************************************************************************Setting up*/
//OK
//Start robot behind first intersection, in the case where there is a
//wall right in front of the robot
void setup() {
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);

  leftServoAngle = 90;
  rightServoAngle = rightServoMap(90);

  pinMode(frontWall, INPUT);
  pinMode(rightWall, INPUT);
  pinMode(leftWall, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  
  rightServo.write(rightServoAngle);
  leftServo.write(leftServoAngle);
  delay(2000); //Wait 2 seconds
}


/*************************************************************************************************Loop*/
void loop() { 
  //Could combine outer left and outer right line sensors 
  // greater than 750 on the line
  // less than 750 off the line
  middleLeftVal = analogRead(middleLeftPin);
  middleRightVal = analogRead(middleRightPin);
  outerLeftVal = analogRead(outerLeftPin);
  outerRightVal = analogRead(outerRightPin);
  
  lineFollow();
  
  //Detect walls
  detectNoFWall = digitalRead(frontWall);
  detectNoRWall = digitalRead(rightWall);
  detectNoLWall = digitalRead(leftWall);

  //intersection
  if((outerLeftVal > threshold) && (outerRightVal > threshold)){
    // use wall sensors to check walls on each side 
    //translate local walls to global walls  = done
    //visited matrix location to find current pos = done
    //change the wall matrix to reflect current wall changes = done 
    
    //dfs to choose where to go next
    Serial.print(robotX);
    Serial.print(" ,");
    Serial.println(robotY);

    if (robotOrientation == NORTH){
    Serial.println("NORTH");
    }
    else if (robotOrientation == EAST) {
    Serial.println("EAST");
    }
    else if (robotOrientation == SOUTH) {
    Serial.println("SOUTH");
    }
    else if (robotOrientation == WEST) {
    Serial.println("WEST");
    }
    
    Serial.print(visited[0][0]);
    Serial.print(visited[0][1]);
    Serial.print(visited[0][2]);
    Serial.println(visited[0][3]);
    
    Serial.print(visited[1][0]);
    Serial.print(visited[1][1]);
    Serial.print(visited[1][2]);
    Serial.println(visited[1][3]);

    Serial.print(visited[2][0]);
    Serial.print(visited[2][1]);
    Serial.print(visited[2][2]);
    Serial.println(visited[2][3]);

    Serial.print(visited[3][0]);
    Serial.print(visited[3][1]);
    Serial.print(visited[3][2]);
    Serial.println(visited[3][3]);

    Serial.print(visited[4][0]);
    Serial.print(visited[4][1]);
    Serial.print(visited[4][2]);
    Serial.println(visited[4][3]);
/**************************************************************************************************DFS*/
    //dfs
    //when we are at a new position (at intersection)
    //IF NEW PLACE EXISTS FROM CURRENT POSITION
    //check walls and surrounded areas' visited states

    neighbourIndex();   //so it'll set front back left right indexes correctly based on the robot orientation
    updateWallMatrix();
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
      cardinalStackStraight();
      stack_push(robotX, robotY);
    }
    else if (detectNoLWall && visited[yleft][xleft] == 0 && withinMazeX(xleft) && withinMazeY(yleft)) {
      //go left
      //update visited to reflect new current position and set the old current position to 1
      Serial.println("turn left");
      leftTurn();
      //add to stack 
      turnStack[stackIndex] = RIGHT;
      cardinalStackLeftTurn();
      stack_push(robotX, robotY);
    } 
    else if (detectNoRWall && visited[yright][xright] == 0 && withinMazeX(xright) && withinMazeY(yright)) {
      Serial.println("turn right");
      rightTurn();
      //go right
      //update visited to reflect new current position and set the old current position to 1
      //add to stack
      turnStack[stackIndex] = LEFT; 
      cardinalStackRightTurn();
      stack_push(robotX, robotY);        
    } 
    else {
      //turn 180 degrees
      if (doOpposite==true){
      opposite();
     
      }
      //backtracking code to prevent infinite loop
      backtrack();
      //helper function: pop current position, go to previous position, 
      //check left and right sides for unvisited and walls (priority)
      //if both are not possible, then go to previous in stack
    }
  }
  else{
    lightUp();

  }
}
  

