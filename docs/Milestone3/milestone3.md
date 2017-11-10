 
## Milestone3

 Real-time Maze mapping
 * The real-time maze mapping is the real time implementation of the simulation done above using a robot. In order to do this, we started by adding helper functions that would allow us to incorporate the additional wallsensors, backtracking, and mainly searching algorithm. We used modular design by dividing our code into main explorer and helper function codes. 
 * Below are the major components of the codes that will finally be used in order to implement depth first search algorithm.
      * Direction specification:  NORTH = 1(0001), EAST  = 2(0010), SOUTH = 4(0100), WEST  = 8(1000).
      * Visited Matrix: used to keep track of the matrices that are already visited by the robot. We assume that all matrices are unvisited except for the matrix on the bottom right corner which is where the robot starts its exploration on the maze. 
         * unvisited =0 and visited =1
     * Wall matrix: used to keep track of wall locations. It is initialized in a way that sets a boundary value for the walls across the 4x5 maze. For instance the (0,0) position has wall locations set by 9(1001) which implies that there is a wall on the NORTH and WEST side by default. 
     
#### Helper Functions
* Robot orientation- 
* resetindex-
* index-
* update visited: 
* Wall orientation-
* update_WallMatrix-
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
 
