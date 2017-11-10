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

void rightturn() {
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

void leftturn(){
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
  byte pos [2]= [x, y];
  stack[stackIndex] = pos;
  on_stack[pos] = true;
  stackIndex++;
}

// Return true if the stack is empty. Only works on the stack defined globally as int stack[50].
bool stack_empty() {
  return (stackIndex == 0);
}

// Return the value on top of the stack.
// int stack_top() {
//   if (stack_empty()) return NULL;
//   return stack[stackIndex-1];
// }



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
  stack_pop();
  lineFollow();
  
  
if (!detectLwall) {
  if (visited[xleft][yleft]==0){
    //go left
    //update visited to reflect new current position and set the old current position to 1
    leftturn();
    //add to stack 
    stack_push(robotX, robotY);
  }
}

else (!detectRwall) {
  if (visited[xright][yright]==0){
    //go right
    //update visited to reflect new current position and set the old current position to 1
    rightturn();
    //add to stack 
    stack_push(robotX, robotY);
  }
}
  
  
