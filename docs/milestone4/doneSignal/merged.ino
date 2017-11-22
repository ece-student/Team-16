/* 
 *    Maze mapping Robot with transmission and dfs
 *  
 *  
 *  
 *  
 *  
 */

#include <Servo.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


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


/************************************************************************************radio stuff start*/
// doneSignal pin
char doneSignalForMaze= 7;

// Set up nRF24L01 radio on SPI bus plus pins 3 & 4
RF24 radio(9,10);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0x0000000038LL, 0x0000000039LL };

// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role = role_pong_back;

/**************************************************************************************radio stuff end*/


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
              WEST  = 8,
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

byte robotX = NULL;
byte robotY = NULL;

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
                       {0,0,0,0}};
                  
byte wall[5][4] = {{9,1,1,3},
                   {8,0,0,2},
                   {8,0,0,2},
                   {8,0,0,2},
                   {12,4,4,6}};
                   
word makeSend [5][4];

byte posStack [20][2];

byte turnStack [20];

byte cardinalStack [30];

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
  if (robotX==NULL  && robotY==NULL){
    xfront=3;
    yfront=4;
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

word assemble(word x, word y) {
  word xShift = x;
  xShift << 14;
  word yShift = y;
  yShift << 11;
  word base = xShift || yShift;
  base = base || (visited[y][x] << 8);
  base = base || (wall[y][x] << 4); 
}


void make2send(){
  for (int i=0; i<5; i++){
    for (int j=0; j<4; i++){
      makeSend[i][j]= assemble (robotX,robotY);
    }
  }
}


//Need  to verify when to update robot current position
void goStraight(){
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(150);
    
if (robotX == NULL && robotY == NULL) {
      robotX = 3;
      robotY = 4;
      visited[robotY][robotX] = 6;
    } 
    else {
      visited[yfront][xfront]=6;
      visited[robotY][robotX] = 1;
      robotX = xfront;
      robotY = yfront;
    }    
    

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

bool cardinalStack_empty(){
  return (stackIndex==0);
}
// Return the value on top of the stack.
//Need to verify
int turnStack_top () {
  if (turnStack_empty()) return NULL;
  return turnStack[stackIndex];
}

//THIS IS FOR THE TURN STUFF, USE BOTH
ORIENTATION from (){
  return robotOrientation;
}

ORIENTATION to() {
  if (cardinalStack_empty()) return NULL;
  return cardinalStack[stackIndex];
}

void printer(){
  
  Serial.println("this is the cardinal stack!");
  Serial.print("[");
  Serial.print(cardinalStack[0]);
  Serial.print(", ");
  Serial.print(cardinalStack[1]);
  Serial.print(", ");
  Serial.print(cardinalStack[2]);
  Serial.print(", ");
  Serial.print(cardinalStack[3]);
  Serial.print(", ");
  Serial.print(cardinalStack[4]);
  Serial.print(", ");
  Serial.print(cardinalStack[5]);
  Serial.print(", ");
  Serial.print(cardinalStack[6]);
  Serial.print(", ");
  Serial.print(cardinalStack[7]);
  Serial.print(", ");
  Serial.print(cardinalStack[8]);
  Serial.print(", ");
  Serial.print(cardinalStack[9]);
  Serial.print(", ");
  Serial.print(cardinalStack[10]);
  Serial.print(", ");
  Serial.print(cardinalStack[11]);
  Serial.print(", ");
  Serial.print(cardinalStack[12]);
  Serial.print(", ");
  Serial.print(cardinalStack[13]);
  Serial.print(", ");
  Serial.print(cardinalStack[14]);
  Serial.print(", ");
  Serial.print(cardinalStack[15]);
  Serial.print("]");

}

void cardinalTurn(){
  Serial.print("to :");
  Serial.println(to());
  Serial.print("from :");
  Serial.println(from());
  
//  straight
  if (from()==to()){
    goStraight;
  }
  
  //right
  else if (from()==1 && to()==2){
    rightTurn();
  }
  else  if (from()==4 && to()==8){
    rightTurn();
  }
  else if (from()==8 && to()==1){
    rightTurn();
  }
  else if (from()==2 && to()==4){
    rightTurn();
  }
  
  //left
  else if (from()==1 && to()==8){
    leftTurn();
  }
  else if (from()==4 && to()==2){
    leftTurn();
  }
  else if (from()==8 && to()==4){
    leftTurn();
  }
  else if (from()==2 && to()==1){
    leftTurn();
  }
  
  //opposite
  else if (from()==1 && to()==4){
    opposite();
  }
  else if (from()==4 && to()==1){
    opposite();
  }
  else if (from()==8 && to()==2){
    opposite();
  }
  else if (from()==2 && to()==8){
    opposite();
  }
  
  
  
}
  

//OK
void stack_pop() {
  if (stack_empty()) return ;
  stackIndex--;
}


void cardinalStackLeftTurn(){
  Serial.println("cardinal stack left turn");
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
    Serial.println("cardinal stack right turn");
  
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
  Serial.println("cardinal stack straight");
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
  Serial.println("in backtrack");

  Serial.print("Stack Index:");
  Serial.println(stackIndex);
  
  
  //while there is not unvisited neighbor 
  while ((!detectNoLWall || visited[yleft][xleft]==1) && (!detectNoRWall || visited[yright][xright]==1) 
  && (!detectNoFWall || visited[yfront][xfront]==1) && !cardinalStack_empty()){
    //using from and to, determine direction of     
    cardinalTurn();
    neighbourIndex();
    stack_pop();
    //at an intersection, read the current orientation and the orientation of the next on, 
    
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


/**************************************************************************************radio stuff start*/
  // Print preamble
  //

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(57600);
  printf_begin();
  printf("\n\rRF24/examples/GettingStarted/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("*** PRESS 'T' to begin transmitting to the other node\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);
  radio.setAutoAck(true);
  // set the channel
  radio.setChannel(0x50);
  // set the power
  // RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setPALevel(RF24_PA_MIN);
  //RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setDataRate(RF24_250KBPS);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  //radio.setPayloadSize(8);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  //**************************************************************************//

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
}

/**************************************************************************************radio stuff ends*/
  



/*************************************************************************************************Loop*/
void loop() { 

/******************************************************************************************radio start*/

//
  // Ping out role.  Repeatedly send the current time
  //

  if (role == role_ping_out)
  {
    // First, stop listening so we can talk.
    radio.stopListening();

    // Take the time, and send it.  This will block until complete
  
    printf("Now sending the word maze");
    bool ok = radio.write( &makeSend, sizeof(word));

    if (ok)
      printf("ok...");
    else
      printf("failed.\n\r");

    // Now, continue listening
    radio.startListening();

    // Wait here until we get a response, or timeout (250ms)
    unsigned long started_waiting_at = millis();
    bool timeout = false;
    while ( ! radio.available() && ! timeout )
      if (millis() - started_waiting_at > 200 )
        timeout = true;

    // Describe the results
    if ( timeout )
    {
      printf("Failed, response timed out.\n\r");
    }
    else
    {
      // Grab the response, compare, and send to debugging spew
      unsigned long got_time;
      radio.read( &got_time, sizeof(unsigned long) );

      // Spew it
      printf("Got response %lu, round-trip delay: %lu\n\r",got_time,millis()-got_time);
    }

    // Try again 1s later
    delay(1000);



  }
//**************************************************************************//
  //
  // Pong back role.  Receive each packet, dump it out, and send it back
  //

  if ( role == role_pong_back )
  {
    // if there is data ready
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      unsigned long got_time;

//**************************************************************************//
        
//ADDED RECEIVER CODE STARTS

unsigned char got_data;
bool done = false;
while (!done)
{
  // Fetch the payload, and see if this was the last one.
  done = radio.read( &got_data, sizeof(unsigned char) );

  // Spew it
  // Print the received data as a decimal
  printf("Got payload %d...",got_data);
  if (got_data==0){
    pinMode(doneSignalForMaze, OUTPUT);
    digitalWrite(doneSignalForMaze, HIGH);
  }

  // Delay just a little bit to let the other unit
  // make the transition to receiver
  delay(20);

}
 
//**************************************************************************//
  

      // First, stop listening so we can talk
      radio.stopListening();

      // Send the final one back.
      radio.write( 8, sizeof(unsigned long) );
      printf("Sent response.\n\r");

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  

  //
  // Change roles
  //

  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back )
    {
      printf("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK\n\r");

      // Become the primary transmitter (ping out)
      role = role_ping_out;
      radio.openWritingPipe(pipes[0]);
      radio.openReadingPipe(1,pipes[1]);
    }
    else if ( c == 'R' && role == role_ping_out )
    {
      printf("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK\n\r");

      // Become the primary receiver (pong back)
      role = role_pong_back;
      radio.openWritingPipe(pipes[1]);
      radio.openReadingPipe(1,pipes[0]);
    }
  }
}

/********************************************************************************************radio end*/


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
      printer();
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
    if (detectNoFWall && ((visited[yfront][xfront] == 0 && withinMazeX(xfront) && withinMazeY(yfront)) || (robotX == NULL && robotY == NULL ))) {
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
    else if (detectNoLWall && ((visited[yleft][xleft] == 0 && withinMazeX(xleft) && withinMazeY(yleft)) || (robotX == NULL && robotY == NULL))) {
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
  

