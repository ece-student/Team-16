
Graphics Subteam

The ultimate goal is to be able to map the robot's path through the maze on a screen using a FPGA and a VGA. In order to do this, the lab was split into multiple steps: Reading external inputs to FPGA, correctly updating a 4-bit array dependent on the inputs, drawing one box on the screen, description of how the DAC on the provided VGA connectors works and how the resistor values were chosen, and mapping external inputs to four different outputs on the screen.


For the first part, we simply wanted to show that the 


## Description of how resistor values were chosen

* We had three resisotrs for red and blue and two resistors for green color output from the VGA.
* The resistor values were calcuated by using voltage divider concept. 
* We calcualted the voltage drop across the 50 Ohm resistor (labeled R4) by turining on only one resitor connected to the VGA pin. 
* The voltage drop across a bit is twice the voltage of the next most significant bit. 
* For Red and Blue colors

   | Resistor    | Voltage       |  
   | ----------- | ------------- |
   | R1  (MSB)   | V1=2V2=4V3    |     
   | R2  (2nd MSB| V2=2V3        |    
   | R3  (3rd MSB| V3            |   
   
   *V1+V2+V3 = 1V*
   *4V3+2V3+V3 = 1V*
   *7V3= 1V*
   *V3= 1/7V*
