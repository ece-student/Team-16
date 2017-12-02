# Final System Design
Upon completion of milestone 4, our robot still needed additional work on the following components in order to be fully-functioning for competition
## Hardware Redesign

## Code Merging
In the line following/DFS code, we inserted the treasure detection code. Since the robot pauses momentarily to process its position and decide its next move at each intersection, we merged the treasure detection code into the block pertaining to interdsection processing. to save memory, we changed our 
We also needed to implement a previously unfamiliar circuit, a passive mixer, in order to have all of our treasure detectors connect to a single pin. In theory, the basic treasure detection functionality was performing, but used three different analog inputs in the solution. Here, as we do not have the privilege of many available pins on our arduino, we used a passive mixer that would allow us to use only one pin. 

The passive mixer is required b

## Radio Communication

## Search Algorithm

## Mux
