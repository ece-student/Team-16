
Graphics Subteam

The ultimate goal is to be able to map the robot's path through the maze on a screen using a FPGA and a VGA. In order to do this, the lab was split into multiple steps: Reading external inputs to FPGA, correctly updating a 4-bit array dependent on the inputs, drawing one box on the screen, description of how the DAC on the provided VGA connectors works and how the resistor values were chosen, and mapping external inputs to four different outputs on the screen.


For the first part, we simply wanted to show that the 


## Description of how resistor values were chosen

* We had three resisotrs for red and blue and two resistors for green color output from the VGA.
* The resistor values were calcuated by using voltage divider concept. 
* We calcualted the voltage drop across the 50 Ohm resistor (labeled R4) by turining on only one resitor connected to the VGA pin. 
* The voltage drop across a bit is twice the voltage of the next most significant bit. 
* For Red and Blue colors

   | Resistor    | Voltage       |  Voltage  |calculated | Measured|
   | ----------- | ------------- |-----------|---------- |-------- |
   | R1  (MSB)   | V1=2V2=4V3    | 4/7V      |238.75Ohms |         |
   | R2  (2nd MSB| V2=2V3        | 2/7V      |527.5Ohms  |         |
   | R3  (3rd MSB| V3            | 1/7V      |1105Ohms   |         |
   
   * How each voltages were computed:
   
   *V1+V2+V3 = 1V*
   
   *4V3+2V3+V3 = 1V*
   
   *7V3= 1V*
   
   *V3= 1/7V*
   
   * How each resitances were computed:
   
   _Vin= 3.3V (input to FPGA)_
   
   _Vi = [R4/(R4+Ri)] x Vin , i= 1,2,3_ 
   
  * For Green color
  
   | Resistor    | Voltage    |  Voltage  |Calcualted|
   | ----------- | -----------|-----------|----------|
   | R1  (MSB)   | V1=2V2     | 2/3       |197.5Ohms |
   | R2  (2nd MSB| V2         | 1/3       |445Ohms   |
   
   How each voltages were computed:
   
   *V1+V2 = 1V*
   
   *2V2+V2 = 1V*
   
   *3V2= 1V*
   
   *V2= 1/3V*
   
   ### External Input
   Reistor values 464.8 Ohms and 895 Ohms
   divider voltag value 3.37 volts
  
  
  
   