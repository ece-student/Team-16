
Radio Team
RF24 is ...
The main goals of radio team are:
* Sending information wirelessly between Arduino’s
* Sending the entire maze wirelessly
* Updating the maze array, dependent only on the updated robot information

# Sending information wirelessly between Arduino’s
* We started by downloading and installing the [RF24 Arduino library](https://github.com/maniacbug/RF24) and updated the getting started sketch from the  3400 course webiste.
* The first step was assigining the identifier or address number for the two pipes: in this case they represent the address of transmitter and receiver. We used the openWritingpipe command to do this. 
`arduino







Graphics Team
* Displaying a full 4-by-5 grid array on the screen
* Communicating maze information from the Arduino to the FPGA
* Display the robot location on the screen
* Distinguish what sites have been visited and which haven’t on the screen
