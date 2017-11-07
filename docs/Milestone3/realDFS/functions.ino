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
  for (int i =0; i<5;i++){
    for (int j=0; j<4; j++){
     if (visited[i][j]== 6){
      visited[i][j]==1;
      // add new current position
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

