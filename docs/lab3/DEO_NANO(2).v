//=======================================================
// ECE3400 Fall 2017
// Lab 3: Template top-level module
//
// Top-level skeleton from Terasic
// Modified by Claire Chen for ECE3400 Fall 2017
//=======================================================

`define ONE_SEC 25000000


module DE0_NANO(

	//////////// CLOCK //////////
	CLOCK_50,

	//////////// LED //////////
	LED,

	//////////// KEY //////////
	KEY,

	//////////// SW //////////
	SW,

	//////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	GPIO_0_D,
	GPIO_0_IN,

	//////////// GPIO_0, GPIO_1 connect to GPIO Default //////////
	GPIO_1_D,
	GPIO_1_IN
);

 
	 //=======================================================
	 //  PARAMETER declarations
	 //=======================================================

	 localparam ONE_SEC = 25000000; // one second in 25MHz clock cycles
	 
	 //=======================================================
	 //  PORT declarations
	 //=======================================================

	 //////////// CLOCK //////////
	 input 		          		CLOCK_50;

	 //////////// LED //////////
	 output		     [7:0]		LED;

	 /////////// KEY //////////
	 input 		     [1:0]		KEY;

	 //////////// SW //////////
	 input 		     [3:0]		SW;

	 //////////// GPIO_0, GPIO_0 connect to GPIO Default //////////
	 inout 		    [33:0]		GPIO_0_D;
	 input 		     [1:0]		GPIO_0_IN;

	 //////////// GPIO_0, GPIO_1 connect to GPIO Default //////////
	 inout 		    [33:0]		GPIO_1_D;
	 input 		     [1:0]		GPIO_1_IN;
	  

    //=======================================================
    //  REG/WIRE declarations
    //=======================================================
    reg         CLOCK_25;
	 
	 reg [1:0] row_1;
	 reg [1:0] row_2;
	 
	 reg [7:0] grid [1:0] [1:0];

	 wire [1:0] x_coord;
	 wire [1:0] y_coord;

	 wire high_x_coord;
	 wire high_y_coord;
	 
    wire        reset; // active high reset signal 

    wire [9:0]  PIXEL_COORD_X; // current x-coord from VGA driver
    wire [9:0]  PIXEL_COORD_Y; // current y-coord from VGA driver
    reg [7:0]  PIXEL_COLOR;   // input 8-bit pixel color for current coords
	 
	 reg  [24:0] led_counter; // timer to keep track of when to toggle LED
	 reg 			led_state;   // 1 is on, 0 is off
	 
    // Module outputs coordinates of next pixel to be written onto screen
    VGA_DRIVER driver(
		  .RESET(reset),
        .CLOCK(CLOCK_25),
        .PIXEL_COLOR_IN(PIXEL_COLOR),
        .PIXEL_X(PIXEL_COORD_X),
        .PIXEL_Y(PIXEL_COORD_Y),
        .PIXEL_COLOR_OUT({GPIO_0_D[9],GPIO_0_D[11],GPIO_0_D[13],GPIO_0_D[15],GPIO_0_D[17],GPIO_0_D[19],GPIO_0_D[21],GPIO_0_D[23]}),
        .H_SYNC_NEG(GPIO_0_D[7]),
        .V_SYNC_NEG(GPIO_0_D[5])
    );
	 
	 assign reset = ~KEY[0]; // reset when KEY0 is pressed
	 
	 reg [1:0] EXSW;
	 reg [1:0] EXSW1;
	 
//	 assign EXSW = GPIO_0_D[2];
//	 assign EXSW1 = GPIO_0_D[4];
	 
	 assign LED[0] = led_state;
	 
//	 assign LED[0] = EXSW;
//	 assign LED[1] = EXSW1;
	 
	 
//	 assign LED[0] = grid[0][0];
//	 assign LED[1] = grid[0][1];
//	 assign LED[2] = grid[1][0];
//	 assign LED[3] = grid[1][1];
 
    //=======================================================
    //  Structural coding
    //=======================================================
 
	 // Generate 25MHz clock for VGA, FPGA has 50 MHz clock
    always @ (posedge CLOCK_50) begin
        CLOCK_25 <= ~CLOCK_25; 
    end // always @ (posedge CLOCK_50)
	
	 // Simple state machine to toggle LED0 every one second
//	 always @ (posedge CLOCK_25) begin
//		  if (reset) begin
//				led_state   <= 1'b0;
//				led_counter <= 25'b0;
//		  end
//		  
//		  if (led_counter == ONE_SEC) begin
//				led_state   <= ~led_state;
//				led_counter <= 25'b0;
//		  end
//		  else begin	
//				led_state   <= led_state;
//				led_counter <= led_counter + 25'b1;
//		  end // always @ (posedge CLOCK_25)
//	 end



	 always @ (posedge CLOCK_25) begin
	 if (GPIO_0_D[2] == 0) begin
		  if (reset) begin
				led_state   <= 1'b0;
				led_counter <= 25'b0;
		  end
		  
		  if (led_counter == ONE_SEC) begin
				led_state   <= ~led_state;
				led_counter <= 25'b0;
		  end
		  else begin	
				led_state   <= led_state;
				led_counter <= led_counter + 25'b1;
		  end // always @ (posedge CLOCK_25)
		end
	 end

	
	// for having 4 squares appear on the screen
	always @ (*) begin 
		  if(PIXEL_COORD_X < 10'd64 && PIXEL_COORD_Y < 10'd64) begin
				PIXEL_COLOR <= 8'b000_000_00;
		  end
		  else begin
				PIXEL_COLOR <= 8'b111_000_00;
		  end
   end
	
	

endmodule
