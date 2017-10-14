
Graphics Subteam

The ultimate goal is to be able to map the robot's path through the maze on a screen using a FPGA and a VGA. Inorder to do this, the lab was split into multiple steps: Reading external inputs to FPGA, correctly updating a 4-bit array dependent on the inputs, drawing one box on the screen, description of how the DAC on the provided VGA connectors works and how the resistor values were chosen, and mapping external inputs to four different outputs on the screen.


## Reading external inputs to FPGA


For the first part, reading external inputs to FPGA, we simply wanted to show that we could use external inputs to invoke some reaction on the FPGA. In order to do this, we chose to use an arduino to create the external input.

The arduino will output some coded voltage to a voltage divider, since the arduino can only output 5V but the FPGA can only accept inputs of roughly 3.3V. Then we input that value into the FPGA. We then code using Verilog to turn on or off an LED based on whether or not the value from the arduino is high or low.


We toggled the arduino output pin from LOW to HIGH every 2 seconds using the following code:

'''
  //External input to FPGA
  //should toggle from HIGH to LOW every 2 seconds
  
  digitalWrite(Pin1, LOW);         // sets the pin low
  digitalWrite(LED_BUILTIN, LOW);  //sets the LED low (just a marker)
  delay(2000);                     // waits for 2 seconds
  digitalWrite(Pin1, HIGH);        // sets the pin high
  digitalWrite(LED_BUILTIN, HIGH); //sets the LED high (just a marker)
  delay(2000);                     // waits for 2 seconds

'''

[See the demo here]()


## Correctly updating a 4-bit array dependent on the inputs

This is similar to the external input to the FPGA with one added aspect. Since we want a 4 bit array, or essentially a 2 by 2 grid array, we can use two inputs from the arduino and map each part of the grid to the corresponding LED on the FPGA.

For the arduino code, we had two outputs, but we wanted to use these outputs to create a total of 4 combinations, as seen on the diagram.
'''
  //4 bit array mapped to LEDs on FPGA
  //should iterate through 00, 01, 10, 11 
  //2 second intervals
  
digitalWrite(Pin1, LOW);      // sets both the pins low
digitalWrite(Pin2, LOW);      
delay(2000);                  // waits for 2 seconds

digitalWrite(Pin1, LOW);      // sets pin1 low
digitalWrite(Pin2, HIGH);     // sets pin2 high
delay(2000);                  // waits for 2 seconds


digitalWrite(Pin1, HIGH);     // sets pin1 high
digitalWrite(Pin2, LOW);      // sets pin2 low
delay(2000);                  // waits for 2 seconds


digitalWrite(Pin1, HIGH);     // sets both pins high
digitalWrite(Pin2, HIGH);     
delay(2000);                  // waits for 2 seconds
'''

[See the demo here]()

## Drawing one box on the screen

## Description of how resistor values were chosen

* We had three resisotrs for red and green and two resistors for blue color output from the VGA.
* The resistor values were calcuated by using voltage divider concept. 
* We calcualted the voltage drop across the 50 Ohm resistor (labeled R4) by turining on only one resitor connected to the VGA pin. 
* The voltage drop across R4 is determined by the bit that is one and each bit generates an output voltage that is twice the voltage output of the next least significant bit. 
* For Red and Green colors

   | Resistor    | Voltage output|  Voltage  |calculated | Measured|
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
   
  * For Blue color
  
   | Resistor    | Voltage    |  Voltage  |Calcualted|
   | ----------- | -----------|-----------|----------|
   | R1  (MSB)   | V1=2V2     | 2/3       |197.5Ohms |
   | R2  (2nd MSB| V2         | 1/3       |445Ohms   |
   
   How each voltages were computed:
   
   *V1+V2 = 1V*
   
   *2V2+V2 = 1V*
   
   *3V2= 1V*
   
   *V2= 1/3V*
   c
   ### External Input
   Reistor values 464.8 Ohms and 895 Ohms
   divider voltage value 3.37 volts
  
  
  
   
