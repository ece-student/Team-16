
# Final System Design
Main tasks during the final week for our robot
 * Hardware
    * Redesinging
    * Micamplifier - we made a mic amplifier using the PCB for the final system. Unfortunately, there were connection problems on the amplifier that prevented it from working properly. Based on the results we had from lab2 we were expecting to get an output o
    * Push-button - the push button is our back up robot starting switch if in case our mic system fails to detect 600Hz and set the robot into motion. 
    * Passive mixer for treasure sensors: since the Arduino has only five pins we needeed to figure out a way to limit the number of inputs that are needed to directly connect with the Arduino. The passive mixer helped us to  
    * Wall sensor for distance modification:
* Software
    * Merging Code
     * Treasure sensor and line following
     * Receiving code
 Specification for major components of robot
 * Pin List
 * Sensitivity of IR sensor:
  * Output vs distane of treasure
  * Signal to noise ratio
  * Resistance to ambient light
 * Sensitivity of microphone
  * Output vs distance
 * Bandwidth of communication
 * Computation speed and memory usage
 * Robot
  * Worst and best case scenarios for robot or DFS
  * speed and power of servos
  * Straight line velocity
  * Turn speed and radis
  
 * Mapped system
 
  
 
 
 
 
 
      
      
    
Upon completion of milestone 4, our robot still needed additional work on the following components in order to be fully-functioning for competition
## Hardware Redesign

## Code Merging
In the line following/DFS code, we inserted the treasure detection code. Since the robot pauses momentarily to process its position and decide its next move at each intersection, we merged the treasure detection code into the block pertaining to interdsection processing. to save memory, we changed our 
We also needed to implement a previously unfamiliar circuit, a passive mixer, in order to have all of our treasure detectors connect to a single pin. In theory, the basic treasure detection functionality was performing, but used three different analog inputs in the solution. Here, as we do not have the privilege of many available pins on our arduino, we used a passive mixer that would allow us to use only one pin. 

The passive mixer is required b

## Radio Communication

## Search Algorithm

## Pin 
