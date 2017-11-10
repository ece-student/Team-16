 
#### Milestone3

 Real-time Maze mapping
 * For implementing the real-time algorithm fwe started by adding helper functions that would allow us to incorporate the additional wall
 sensors, backtracking, and mainly searching. We also made separate files for exploring and functions in order to make a modular design. 
 * Below are the major components of the code that will finally be used in order to implement depth first search algorithm.
      * Direction specification:  NORTH = 1, EAST  = 2, SOUTH = 4, WEST  = 8
      * Visited Matrix: used to keep track of the matrices that are already visited by the robot
      * Wall matrix: used to keep track of walll locations. It is initialized in a way that sets a boundary value for the walls across the         maze. For instance 9 
     
      byte wall[5][4] = {{9,1,1,3},
                   {8,0,0,2},
                   {8,0,0,2},
                   {8,0,0,2},
                   {12,4,4,6}};
      
  
  * We used amplifiers for wall sensors
      
 
 
 
 * Helper functions
 * DFS
 * Demo
 algorithm for real simulation code
 *  use wall sensors to see wher ethe walls are locally
 * translate local postion to global positon(that is going to be used by countring counters)
 * use the visited matrix to determine the current position and then use that current position to write to the wall matrix
 * determine where to go next and then update the visited matrix, and go to that position
 
