
## Lab 2: 
### For this lab, we split up into 2 subteams blah blah blah




## Acoustic Team:

### The goal of this sublab was to enable our robot to detect a 660hz frequency. IN order to do this we had to alsoo have a correct FFT analysis, have a working amplifier circuit and also be able to distinguish a 660 hz from a 585hz and 735 hz.

and distinguish it from a Correct FFT analysis
2 points: Working amplifier circuit
3 points: Distinguish a 660Hz tone (from tones at 585Hz and 735Hz)

**Introduction**

For this lab, we needed a microphone, arduino uno, and some resistors and capacitors. We did not have to assemble the microphone circuit as in past years since the microphone we used (MAX4466) already came with a low pass filter, which meant that we would not have to use the capacitor and 3 kohm resistor. 

However, we still wanted to check if the microphone worked properly, so we connected it to the arduino and connected the arduino to the laptop to power it.

Then we hooked it up to the oscilloscope, turned on the 660 Hz (moving around the potentiometer to change gain) and adjusted the scale. In the video, in the oscilloscope measurement you can see it says 660 Hz, reconfirming that it has read the correct value.

**FFT analysis**

We decided to use analogRead. Note that when we use fft_input, each index i that is even represents a real signal, whereas the odd signals are the imaginary components. Thus in the loop

 for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      fft_input[i] = analogRead(A0); // put real data into even bins
      fft_input[i+1] = 0; // set odd bins to 0

We have the the even index 1 equal to the analogRead from pin A0, an i+1 index (the odd one) equal to zero.
Then the for loop is incremented by two.

To check the code and make sure it was working correctly, we hooked it up to the function generator. We also hooked up the oscilloscope to make sure the function generator was outputting as well.

Afterwards we want to map the data onto a graph and see if the bin at 660 hz, aka 17.6 is the highest. 

However, it ended up for us being in the 20th bin, however it should not matter, since it works relatively and we knew for sure that we used the 660 hz


**Amplifier Circuit**

We still need to make the amplifier however, because the sound had to be relatively close to the microphone for it to pick up any signal. However rather than making a filter and an amplifier separately, we decided to make a bandpass filter with gain.

Using [this website](analog.com/designtools/en/filterwizard/) we mapped out what we wanted our Bode plot to look like, such that our 660 Hz signal would be amplified but all others would be minimized. We first started off with a gain of 40db, or 100, however we decided to decrease this value to 20db, or 10. The website then outputs a bandpass filter circuit schematic.
Note that on the website it will output a circuit for voltage range from 5V to -5V, however we want from 5V to 0V. If you change this value, they will give you a REF schematic as well. However this is unnecessary. We simply used a voltage divider to connect the REF and give each 2.5V.

Bode plot pic
filter circuit pic






