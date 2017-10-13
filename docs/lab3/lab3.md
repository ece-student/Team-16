
Graphics Subteam


The ultimate goal is to be able to map the robot's path through the maze on a screen using a FPGA and a VGA. In order to do this, the lab was split into multiple steps: Reading external inputs to FPGA, correctly updating a 4-bit array dependent on the inputs, drawing one box on the screen, description of how the DAC on the provided VGA connectors works and how the resistor values were chosen, and mapping external inputs to four different outputs on the screen.


**Reading external inputs to FPGA**

For the first part, reading external inputs to FPGA, we simply wanted to show that we could use external inputs to invoke some reaction on the FPGA. In order to do this, we chose to use an arduino to make the external input. 

The arduino will output some coded voltage to a voltage divider, since the arduino can only output 5V but the FPGA can only accept inputs of roughly 3.3V. Then we input that value into the FPGA. We then code using Verilog to turn on or off an LED based on whether or not the value from the arduino is high or low.

We did this through the following code:

```
```

[See the demo here]()

**Correctly updating a 4-bit array dependent on the inputs**

This is similar to the external input to the FPGA with one added aspect. Since we want a 4 bit array, or essentially a 2 by 2 grid array, we can use two inputs from the arduino and map each part of the grid to the corresponding LED on the FPGA.

We did this through the following code:

```
```

[See the demo here]()
