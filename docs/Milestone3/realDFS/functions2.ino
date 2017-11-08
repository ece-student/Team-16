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
}

void goStraight(){
    rightServoAngle = rightServoMap(180);
    leftServoAngle = 180;
    rightServo.write(rightServoAngle);
    leftServo.write(leftServoAngle);
    delay(150);
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


