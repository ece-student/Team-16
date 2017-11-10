/* 
 *  Helper Functions
 *  
 *  
 *  
*/
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
void resetindexstuff(){
   xleft=robotX; 
   yleft=robotY;
   xfront=robotX;
   yfront=robotY;
   xright=robotX;
   yright=robotY;
   xback=robotX;
   yback=robotY;
}

void indexstuff(){
   if(robotOrientation == NORTH){
     xleft=robotX-1;
     yleft=robotY;
     xfront=robotX;
     yfront=robotY+1;
     xright=robotX+1;
     yright=robotY;
     xback=robotX;
     yback=robotY-1;
  }
  if(robotOrientation == EAST) {
     xleft=robotX;
     yleft=robotY+1;
     xfront=robotX+1;
     yfront=robotY;
     xright=robotX;
     yright=robotY-1;
     xback=robotX-1;
     yback=robotY;
  }
  if(robotOrientation == SOUTH) {
     xleft=robotX+1;
     yleft=robotY;
     xfront=robotX;
     yfront=robotY-1;
     xright=robotX-1;
     yright=robotY;
     xback=robotX;
     yback=robotY+1;
  }
  if(robotOrientation == WEST) {
     xleft=robotX;
     yleft=robotY-1;
     xfront=robotX-1;
     yfront=robotY;
     xright=robotX;
     yright=robotY+1;
     xback=robotX+1;
     yback=robotY;
  }
}


void updateVisited() {
  visitedBox++;
  for (int i =0; i<5;i++){
    for (int j=0; j<4; j++){
     if (visited[i][j]== 6){
      visited[i][j]==1;
      // add new current position
    }
  }
}
}

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
  updateVisited();
  visited[xright][yright]=6;
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
  updateVisited();
  visited[xback][yback]=6;
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
  updateVisited();
  visited[xleft][yleft]=6;
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
    
    updateVisited();
    visited[xleft][yleft]=6;
    
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



void updateWallMatrix() {
  wall[robotY][robotX] = wallOrientation();
}

byte wallOrientation() {
  byte wall = 0;
  if(robotOrientation == NORTH) {
    if(detectFWall){
      wall |= NORTH;
    }
    if(detectLWall){
      wall |= WEST;
    }
    if(detectRWall){
      wall |= EAST;
    }  
  }
  else if(robotOrientation == EAST) {
    if(detectFWall){
      wall |= EAST;
    }
    if(detectLWall){
      wall |= NORTH;
    }
    if(detectRWall){
      wall |= SOUTH;
    } 
  }
  else if(robotOrientation == SOUTH) {
    if(detectFWall){
      wall |= SOUTH;
    }
    if(detectLWall){
      wall |= EAST;
    }
    if(detectRWall){
      wall |= WEST;
    } 
  }
  else if(robotOrientation == WEST) {
    if(detectFWall){
      wall |= WEST;
    }
    if(detectLWall){
      wall |= SOUTH;
    }
    if(detectRWall){
      wall |= NORTH;
    } 
  }  
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
  
  while (!detectLWall || !detectRWall){
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
      indexstuff();   //so it'll set front back left right indexes correctly based on the robot orientation
      
      middleLeftVal = analogRead(middleLeftPin);
      middleRightVal = analogRead(middleRightPin);
      outerLeftVal = analogRead(outerLeftPin);
      outerRightVal = analogRead(outerRightPin);
      lineFollow();
              
      if (!detectLWall) {
        if (visited[xleft][yleft]==0){
          //go left
          //update visited to reflect new current position and set the old current position to 1
          leftTurn();
          //add to stack 
          stack_push(robotX, robotY);
          return;
        }
      }
  
      else if (!detectRWall) {
        if (visited[xright][yright]==0){
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
    resetindexstuff();    //so it'll set all of x and y values of back left right forward to robot x and y 
  
  }
}




  
