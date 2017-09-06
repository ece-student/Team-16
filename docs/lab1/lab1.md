# Lab 1: Microcontroller

[Lab 1 Handout](https://cei-lab.github.io/ece3400/lab1.html)

This lab was an introductory lab aimed to help us gain familiarity with the Arduino Uno and the Arduino IDE. Using these alongside other external components allowed us to ultimately create an autonomous robot that moved in a four sided path. Each part to this lab is outlined below, as well as the intermediate steps we took.


### Part 1: Blinking an internal LED 
###### (Jidenna)

coming soon


### Part 2: Blinking an external LED 
###### (Jidenna)

coming soon


### Part 3: Reading the value of a potentiometer via the serial port 
######  (Asad)

The previous exercise made use of setting a digital pin to output mode, in order to blink the LED using a simple resistor circuit. This exercises, on the other hand, incorporated the UNO's analog pins and set them to input mode towards the purposes of reading voltage levels. A potentiometer was used to vary the the voltage levels supplied to the UNO. 

The potentiometer has three pins, two of which were connected to PWR or GND. The third pin was connected to our analog pin and set as an input (to receive and read voltages). Similar to our other circuit iterations, we placed a ~300 Ω resister in series with the input pin (A1) that directly interfaces with the breadboard. A1 was passed into the analogRead() function to periodically read the circuit's voltage. To display our results, the serial monitor was initialzied in the setup() block with a baud rate of 9600, and the read voltage value was written to the serial port after every half second interval.

Upon uploading our code, the serial port outputted a value from 0 to 1023 every half second; these readings could be adjusted depending on the knob position of the potentiometer. To see teh varying voltage levels caused by the tuning of the potentiometer, please see the demo below.

### Part 4: Map the value of the potentiometer to the LED 
###### (Lois)

This next exercise is a wonderful way to understand the different inputs and outputs of the arduino. So in the previous exercise we’ve read the value of the potentiometer via the serial port, but for this next step we want to use the potentiometer to change the intensity of an LED light. 

To review, the potentiometer inputs different analog voltages that we can adjust, 1023 being the highest and 0 the lowest.
However the arduino can only output digital signals. The way to get around this is to connect the LED to a digital pin with PWM capability (pins marked with ~). 

As you can see in the image below, we printed the potentiometer readings as before, so that we could keep track of changing readings. 

![LEDpot](imagesLab1/LEDpot.png)


Also, you may notice we used analogWrite. The reason for this is that the potentiometer readings obviously don’t directly translate into LED intensities. We had to map the values of the potentiometer to the brightness levels of the LED separately.

To see the demo of the LED changing intensity, look below in the demo section. 


### Part 5: Map the value of the potentiometer to the servo 
###### (Firehiwot)
The rotation of the servos can be controlled by changing the angle values:
   * First angle values were changed by entering numbers from 0 to 180 from the key board. (90 -stop, 0 - full speed reverse, 180 - full speed ahead)

![ServoAngles](imagesLab1/ServoAngles.png)
     
   * Then we used the potentiometer to provide an analog signal which controls the rotation speed and direction
   * A map function was used to map resistance readings from potentiometer (0 to 1023) to 0 to 180 range

![ServoandPot](imagesLab1/ServoandPot.png)
   
   * We also measured the frequecncy of the signal using oscilloscope which was around 50 Hz and the duty cycle increased as the angle increased.(Checkout the Demos section)
   

### Part 6: Assemble your robot 
###### (Rohit) will add images

We began assembly of the robot by mounting two servos under the chassis board with premade servo mounts. We choice wheels that would fit the servos without additional adjustments. The wheels sit on the back of the robot, so we needed something to hold up the front. We used a ball bearing in the front. We ran into issues with the height of the ball bearning and had to use a longer 3D printed ball bearing mount to keep the ball bearing and chassis level to the floor. 

We used a 9V battery to power the servos, which we attached under the chassis board with velcro. We used velcro to attach a rechargable battery pack to the top of the board to power the Arduino. We used velcro to attach the arduino and a breadboard on top of the battery pack. 

The wiring was simple and done on the breadboard. The PWM digital output pins 5 and 6 were used to control the servos. Each servo used identical circuitry. The digital pins were connected to the servos through a 300 Ohm resistor. The 9V battery supplied the voltage for the servos and the ground on the breadboard was connected to the ground in the arduino.


### Part 7: Driving your robot autonomously 
###### (John)

coming soon


## Helpful links and References
This website gives an overview of servos and rotation angles: [Servo](http://www.seattlerobotics.org/guide/servos.html)

## Demos
  * [Oscilloscope measurements for 0, 90 and 180 degree rotations](https://www.youtube.com/watch?v=w-dbIPHahbE&feature=youtu.be)

* [LED intensity adjustment using potentiometer reading](https://youtu.be/VkdjhSLH_bo)
