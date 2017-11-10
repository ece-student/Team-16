 
## Milestone3

 Real-time Maze mapping
 * The real-time maze mapping is the real time implementation of the simulation done above using a robot. In order to do this, we started by adding helper functions that would allow us to incorporate the additional wallsensors, backtracking, and mainly searching algorithm. We used modular design by dividing our code into main explorer and helper function codes. 
 * Below are the major components of the codes that will finally be used in order to implement depth first search algorithm.
     * Direction specification:  NORTH = 1(0001), EAST  = 2(0010), SOUTH = 4(0100), WEST  = 8(1000).
     * Turn specification: FORWARD = 0 , LEFT =1, RIGHT=2
     * Visited Matrix: used to keep track of the matrices that are already visited by the robot. We assume that all matrices are unvisited except for the matrix on the bottom right corner which is where the robot starts its exploration on the maze. 
         * unvisited =0 , visited =1, current= 6
     * Wall matrix: used to keep track of wall locations. It is initialized in a way that sets a boundary value for the walls across the 4x5 maze. For instance the (0,0) position has wall locations set by 9(1001) which implies that there is a wall on the NORTH and WEST side by default. 
     
#### Helper Functions 
* rightOrientation- To make a right orientation the current orientation is shifted 90 degrees in the clockwise direction. This is used to update the orientation of the robot when it makes a 180 degree turn before back tracking. 
* leftOrientation: has the opposite implemntation of rightOrientation. 
* resetIndex: resets the left, front, right, and left X and Y axis locations of the robot. 
* neighbourIndex- sets front, back, right and left x and Y indices of the neighboring grid locations relative to the robot's orientation. 
* update visited: updates the visited matrix whenever the robot moves along a specific grid so that it doesn't revisit it again unless it has to backtrack.  
* rightTurn- in addition to making the robot make a right turn from the previous code in lab1, this function calls right Orientation, updateVisited matrices to update the robot's location and direction. The grid to the right side is now the current location of the robot once it makes the turn. 
* leftTurn- opposite implemntation of rightTurn. 
* opposite- used for back tracking. In this case the rightOrientation function is called twice to ensure that the direction is updated twice since the robot makes a 180 degree turn. 
* lineFollow- used for making a robot follow a line using the line sensors. 
* goStraight- used for making the robot go Straight ( doesn't use the line sensors). 
* currentPosition- updates robotX and robotY global variables depending on the current positon of the robot. 
* wallOrientation- uses global variables that detect front, left and right wall sensors. Uses a local variable "wall" which is initialized to zero. Then the wall variable is updated depending on the orientation of the robot and where the wall location is.
* update_WallMatrix- updated  
* stack_push-
* stack_pop-
* backtrack-
      
      (Graphics here for showing initialization of wall and visited matrix)
      
      
  * We used amplifiers for wall sensors
      
 
 
 
 * Helper functions
 * DFS
 * Demo
 algorithm for real simulation code
 *  use wall sensors to see wher ethe walls are locally
 * translate local postion to global positon(that is going to be used by countring counters)
 * use the visited matrix to determine the current position and then use that current position to write to the wall matrix
 * determine where to go next and then update the visited matrix, and go to that position
 
