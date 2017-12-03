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
	GPIO_1_IN,
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
	 
	 reg [7:0] grid [3:0] [4:0];
	 reg [3:0] wall_pos[3:0][4:0];
	 wire [7:0] unvisited;
	 wire [7:0] visited;
	 wire [7:0] wall;
	 wire [7:0] seven;
	 wire [7:0] twelve;
	 wire [7:0] seventeen;
	 wire [7:0] current;
	 wire [7:0] done;
	 
	 wire [15:0] out;
	 
	 //wire [7:0] pastOut;
	 
	 //assign out = pastOut;
	 
	 wire [2:0] x_coord; // 4 wide
	 wire [2:0] y_coord; // 5 tall
	 
	 wire high_x_coord;
	 wire high_y_coord;
	 
	 reg [4:0] counter;
	 
    wire        reset; // active high reset signal 
	 wire 		DONE;
	 
    wire [9:0]  PIXEL_COORD_X; // current x-coord from VGA driver
    wire [9:0]  PIXEL_COORD_Y; // current y-coord from VGA driver
    reg [7:0]  PIXEL_COLOR;   // input 8-bit pixel color for current coords
	 
	 reg [24:0] led_counter; // timer to keep track of when to toggle LED
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
	 
//	 SQUARE_GEN square(
//		.CLOCK(CLOCK_25),
//		.RESET(reset),
//		.FREQ(28409),
//		.OUT({GPIO_0_D[10],GPIO_0_D[12],GPIO_0_D[14],GPIO_0_D[16],GPIO_0_D[18],GPIO_0_D[20],GPIO_0_D[22],GPIO_0_D[24],})
//	 );
//
//	SAWTOOTH_GEN saw(
//		.CLOCK(CLOCK_25),
//		.RESET(reset),
//		.FREQ(1329),
//		.OUT({GPIO_0_D[10],GPIO_0_D[12],GPIO_0_D[14],GPIO_0_D[16],GPIO_0_D[18],GPIO_0_D[20],GPIO_0_D[22],GPIO_0_D[24],})
//	);++
	 
//	 SAWTOOTH_SW_GEN sawSwitch(
//		.CLOCK(CLOCK_25),
//		.RESET(reset),
//		.FREQ(221),
//		.SWITCH(KEY[1]),
//		.OUT({GPIO_0_D[10],GPIO_0_D[12],GPIO_0_D[14],GPIO_0_D[16],GPIO_0_D[18],GPIO_0_D[20],GPIO_0_D[22],GPIO_0_D[24],})
//	 );

	TUNE_GEN tune(
		.CLOCK(CLOCK_25),
		.RESET(reset),
		.DONE(GPIO_1_D[4]),
		.FREQ1(1184),
		.FREQ2(1117),
		.FREQ3(1329),
		.TIME(6250000),
		.OUT({GPIO_1_D[9],GPIO_1_D[11],GPIO_1_D[13],GPIO_1_D[15],GPIO_1_D[17],GPIO_1_D[19],GPIO_1_D[21],GPIO_1_D[23],})
	);

	RECEIVE receive(
		.CLOCK(GPIO_0_D[29]), //sck 
		.DATA(GPIO_0_D[31]), // mosi
		.ENABLE(GPIO_0_D[33]), // pin 6
		.OUT(out)
	);
	 
	 assign reset = ~KEY[0]; // reset when KEY0 is pressed
	 assign DONE = GPIO_1_D[4];
	 /*
	 assign grid[0][0] = 8'b11111111;
	 assign grid[1][0] = 8'b11111111; 
	 assign grid[2][0] = 8'b11111111;
	 assign grid[3][0] = 8'b11111111;
	 
	 assign grid[0][1] = 8'b11111111;
	 assign grid[1][1] = 8'b11111111; 
	 assign grid[2][1] = 8'b11111111;
	 assign grid[3][1] = 8'b11111111;
	 
	 assign grid[0][2] = 8'b11111111;
	 assign grid[1][2] = 8'b11111111; 
	 assign grid[2][2] = 8'b11111111;
	 assign grid[3][2] = 8'b11111111;
	 
	 assign grid[0][3] = 8'b11111111;
	 assign grid[1][3] = 8'b11111111; 
	 assign grid[2][3] = 8'b11111111;
	 assign grid[3][3] = 8'b11111111;
	 
	 assign grid[0][4] = 8'b11111111;
	 assign grid[1][4] = 8'b11111111; 
	 assign grid[2][4] = 8'b11111111;
	 assign grid[3][4] = 8'b11111111;
	 */
	 assign unvisited = 8'b11111111; // white
	 assign visited 	= 8'b11111100; // Yellow
	 assign wall 		= 8'b10001000; // browm
	 assign seven 		= 8'b11100000; // red
	 assign twelve 	= 8'b00011100; // green
	 assign seventeen = 8'b00000011; // blue
	 assign current 	= 8'b00111110; // teal
	 assign black  	= 8'b00000000; // black
	 assign done 		= 8'b11101000;
	 
	 assign LED[0] = led_state;
	 
	 
    //=======================================================
    //  Structural coding
    //=======================================================
 
	 // Generate 25MHz clock for VGA, FPGA has 50 MHz clock
    always @ (posedge CLOCK_50) begin
		CLOCK_25 <= ~CLOCK_25;
		
		if (out[15:14] <= 2'd3 && out[13:11] < 3'd5) begin
			if (out[10:8] == 3'b000) begin
				grid[out[15:14]][out[13:11]] <= unvisited;
			end
			else if (out[10:8] == 3'b001) begin
				grid[out[15:14]][out[13:11]] <= visited;
			end
			else if (out[10:8] == 3'b010) begin
				grid[out[15:14]][out[13:11]] <= wall;
			end
			else if (out[10:8] == 3'b011) begin
				grid[out[15:14]][out[13:11]] <= seven;
			end
			else if (out[10:8] == 3'b100) begin
				grid[out[15:14]][out[13:11]] <= twelve;
			end
			else if (out[10:8] == 3'b101) begin
				grid[out[15:14]][out[13:11]] <= seventeen;
			end
			else if (out[10:8] == 3'b110) begin
				grid[out[15:14]][out[13:11]] <= current;
			end
			wall_pos[out[15:14]][out[13:11]] <= out[7:4];
		end
				// Make grid for walls
		
		// Vertical
		if(PIXEL_COORD_X <= 10'd4 && PIXEL_COORD_Y >= 10'd0  && PIXEL_COORD_Y <= 10'd320)begin
			PIXEL_COLOR <= wall; 
		end
		
		else if (PIXEL_COORD_X >= 10'd254 && PIXEL_COORD_X <= 10'd258 && PIXEL_COORD_Y >= 10'd4 && PIXEL_COORD_Y <= 10'd317)begin
			PIXEL_COLOR <= wall; 
		end
		
		// Horizontal
		else if(PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd256	&& PIXEL_COORD_Y <= 10'd4 ) begin
			PIXEL_COLOR <= wall; 
		end
		else if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd318 && PIXEL_COORD_Y <= 10'd320)begin
			PIXEL_COLOR <= wall; 
		end
	
		
		// Row 1
		else if(PIXEL_COORD_X < 10'd64 &&  PIXEL_COORD_Y < 10'd64)begin // COLUMN 1
			PIXEL_COLOR <= grid[2][0];
			
			if(wall_pos[2][0][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd60 && PIXEL_COORD_Y <= 10'd64)begin
					PIXEL_COLOR <= wall; 
				end			
			end
			if(wall_pos[2][0][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd60 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd0 && PIXEL_COORD_Y <= 10'd64)begin
					PIXEL_COLOR <= wall; 
				end

			end
		end
		
		else if(PIXEL_COORD_X < 10'd128 && PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_Y < 10'd64) begin //  COLUMN 2
			PIXEL_COLOR <= grid[1][0];
			if(wall_pos[1][0][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd60 && PIXEL_COORD_Y <= 10'd64)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][0][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd124 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd0 && PIXEL_COORD_Y < 10'd64)begin
					PIXEL_COLOR <= wall; 
				end

			end
			if(wall_pos[1][0][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd68 && PIXEL_COORD_Y >= 10'd0 && PIXEL_COORD_Y < 10'd64)begin
					PIXEL_COLOR <= wall; 
				end

			end
			
			
		end
		else if(PIXEL_COORD_X < 10'd192 && PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_Y < 10'd64) begin // COLUMN 3
			PIXEL_COLOR <= grid[0][0];
			if(wall_pos[0][0][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd60 && PIXEL_COORD_Y <= 10'd64)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][0][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd188 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd0 && PIXEL_COORD_Y < 10'd64)begin
					PIXEL_COLOR <= wall; 
				end

			end
			if(wall_pos[0][0][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd132 && PIXEL_COORD_Y >= 10'd0 && PIXEL_COORD_Y < 10'd64)begin
					PIXEL_COLOR <= wall; 
				end
			end
			
		end
		else if(PIXEL_COORD_X < 10'd256 && PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_Y < 10'd64)begin // COLUMN 4
			PIXEL_COLOR <= grid[3][0];
			if(wall_pos[3][0][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd60 && PIXEL_COORD_Y <= 10'd64)begin
					PIXEL_COLOR <= wall; 
				end
			end

			if(wall_pos[3][0][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd196 && PIXEL_COORD_Y >= 10'd0 && PIXEL_COORD_Y < 10'd64)begin
					PIXEL_COLOR <= wall; 
				end
			end

		end
		
		// Row 2
		else if(PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y <= 10'd128 && PIXEL_COORD_Y >= 10'd64)begin //  && out[7:6] == 2'b00 && out[5:3] == 3'b001)begin
			PIXEL_COLOR <= grid[2][1];
			
			if(wall_pos[2][1][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y <= 10'd68)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[2][1][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd124 && PIXEL_COORD_Y <= 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[2][1][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd60 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y < 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end			
		end
		
		else if(PIXEL_COORD_X < 10'd128 && PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_Y < 10'd128 && PIXEL_COORD_Y >= 10'd64)begin //  && out[7:6] == 2'b01 && out[5:3] == 3'b001)begin
			PIXEL_COLOR <= grid[1][1];
			if(wall_pos[1][1][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y <= 10'd68)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][1][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd124 && PIXEL_COORD_Y <= 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][1][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd124 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y < 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][1][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd68 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y < 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end			
		end
		
		else if(PIXEL_COORD_X < 10'd192 && PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_Y <= 10'd128 && PIXEL_COORD_Y >= 10'd64)begin //  && out[7:6] == 2'b10 && out[5:3] == 3'b001)begin
			PIXEL_COLOR <= grid[0][1];
			if(wall_pos[0][1][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y <= 10'd68)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][1][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd124 && PIXEL_COORD_Y <= 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][1][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd188 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y <= 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][1][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd132 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y <= 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end			
		end
		
		else if(PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_Y <= 10'd128 && PIXEL_COORD_Y >= 10'd64)begin //  && out[7:6] == 2'b11 && out[5:3] == 3'b001)begin
			PIXEL_COLOR <= grid[3][1];
			if(wall_pos[3][1][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y <= 10'd68)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[3][1][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd124 && PIXEL_COORD_Y <= 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[3][1][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd196 && PIXEL_COORD_Y >= 10'd64 && PIXEL_COORD_Y < 10'd128)begin
					PIXEL_COLOR <= wall; 
				end
			end
			
		end
		
		// Row 3
		else if(PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y <= 10'd192 && PIXEL_COORD_Y >= 10'd128)begin //  && out[7:6] == 2'b00 && out[5:3] == 3'b010)begin
			PIXEL_COLOR <= grid[2][2];
			
			if(wall_pos[2][2][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd132)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[2][2][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd188 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[2][2][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd60 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y < 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			
		end
		else if(PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_Y <= 10'd192 && PIXEL_COORD_Y >= 10'd128)begin //  && out[7:6] == 2'b01 && out[5:3] == 3'b010)begin
			PIXEL_COLOR <= grid[1][2];
			if(wall_pos[1][2][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd132)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][2][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd188 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][2][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd124 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[1][2][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd68 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
		end
		else if(PIXEL_COORD_X < 10'd192 && PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_Y < 10'd192 && PIXEL_COORD_Y >= 10'd128)begin //  && out[7:6] == 2'b10 && out[5:3] == 3'b010)begin
			PIXEL_COLOR <= grid[0][2];
			if(wall_pos[0][2][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd132)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][2][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd188 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][2][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd188 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[0][2][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd132 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
		end
		
		else if(PIXEL_COORD_X < 10'd256 && PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_Y < 10'd192 && PIXEL_COORD_Y >= 10'd128)begin //  && out[7:6] == 2'b11 && out[5:3] == 3'b010) begin
			PIXEL_COLOR <= grid[3][2];
			if(wall_pos[3][2][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd132)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[3][2][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd188 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
			end
			if(wall_pos[3][2][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd196 && PIXEL_COORD_Y >= 10'd128 && PIXEL_COORD_Y <= 10'd192)begin
					PIXEL_COLOR <= wall; 
				end
	
			end
		end
		
		// Row 4
		else if(PIXEL_COORD_X < 10'd64 && PIXEL_COORD_Y < 10'd256 && PIXEL_COORD_Y >= 10'd192)begin //  && out[7:6] == 2'b00 && out[5:3] == 3'b011)begin
			PIXEL_COLOR <= grid[2][3];
			if(wall_pos[2][3][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd196)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[2][3][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd252 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[2][3][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd60 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y < 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		
		else if(PIXEL_COORD_X < 10'd128 && PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_Y < 10'd256 && PIXEL_COORD_Y >= 10'd192)begin //  && out[7:6] == 2'b01 && out[5:3] == 3'b011) begin
			PIXEL_COLOR <= grid[1][3];
			
			if(wall_pos[1][3][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd196)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[1][3][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd252 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[1][3][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd124 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
			
			end
			if(wall_pos[1][3][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd68 && PIXEL_COORD_Y >= 10'd192&& PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		else if(PIXEL_COORD_X < 10'd192 && PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_Y < 10'd256 && PIXEL_COORD_Y >= 10'd192)begin //  && out[7:6] == 2'b10 && out[5:3] == 3'b011) begin
			PIXEL_COLOR <= grid[0][3];
			if(wall_pos[0][3][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd196)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[0][3][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd252 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[0][3][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd188 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[0][3][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd132 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		else if(PIXEL_COORD_X < 10'd256 && PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_Y < 10'd256 && PIXEL_COORD_Y >= 10'd192)begin //  && out[7:6] == 2'b11 && out[5:3] == 3'b011)begin
			PIXEL_COLOR <= grid[3][3];
			if(wall_pos[3][3][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd196)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[3][3][2] ==  1'b1) begin//South
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd252 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[3][3][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd196 && PIXEL_COORD_Y >= 10'd192 && PIXEL_COORD_Y <= 10'd256)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		
		// Row 5
		else if(PIXEL_COORD_X < 10'd64 && PIXEL_COORD_Y < 10'd320 && PIXEL_COORD_Y >= 10'd256)begin //  && out[7:6] == 2'b00 && out[5:3] == 3'b100) begin
			PIXEL_COLOR <= grid[2][4];
			if(wall_pos[2][4][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd260)begin
					PIXEL_COLOR <= wall; 
				end
				
			end

			if(wall_pos[2][4][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd60 && PIXEL_COORD_X <= 10'd64 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y < 10'd320)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		
		else if(PIXEL_COORD_X < 10'd128 && PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_Y < 10'd320 && PIXEL_COORD_Y >= 10'd256)begin //  && out[7:6] == 2'b01 && out[5:3] == 3'b100) begin
			PIXEL_COLOR <= grid[1][4];
			if(wall_pos[1][4][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd260)begin
					PIXEL_COLOR <= wall; 
				end
				
			end

			if(wall_pos[1][4][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd124 && PIXEL_COORD_X <= 10'd128 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd320)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[1][4][3] == 1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd64 && PIXEL_COORD_X <= 10'd68 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd320)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		
		else if(PIXEL_COORD_X < 10'd192 && PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_Y < 10'd320 && PIXEL_COORD_Y >= 10'd256)begin //  && out[7:6] == 2'b10 && out[5:3] == 3'b100) begin
			PIXEL_COLOR <= grid[0][4];
			if(wall_pos[0][4][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd260)begin
					PIXEL_COLOR <= wall; 
				end
				
			end

			if(wall_pos[0][4][1] ==  1'b1) begin//EAST
				if (PIXEL_COORD_X >= 10'd188 && PIXEL_COORD_X <= 10'd192 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd320)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
			if(wall_pos[0][4][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd128 && PIXEL_COORD_X <= 10'd132 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd320)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		
		else if(PIXEL_COORD_X < 10'd256 && PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_Y < 10'd320 && PIXEL_COORD_Y >= 10'd256)begin //  && out[7:6] == 2'b11 && out[5:3] == 3'b100) begin
			PIXEL_COLOR <= grid[3][4];
			if(wall_pos[3][4][0] ==  1'b1) begin//north
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd260)begin
					PIXEL_COLOR <= wall; 
				end
			
			end
			if(wall_pos[3][4][3] ==  1'b1) begin//WEST
				if (PIXEL_COORD_X >= 10'd192 && PIXEL_COORD_X <= 10'd196 && PIXEL_COORD_Y >= 10'd256 && PIXEL_COORD_Y <= 10'd320)begin
					PIXEL_COLOR <= wall; 
				end
				
			end
		end
		else if (PIXEL_COORD_X >= 10'd384 && PIXEL_COORD_X < 10'd448 && PIXEL_COORD_Y <= 10'd192 && PIXEL_COORD_Y >= 10'd128) begin
			if (DONE) begin
				PIXEL_COLOR <= done;
			end
			else begin
				PIXEL_COLOR <= black;
			end
		end
//		// vertical grids for inside squares
//		else if(PIXEL_COORD_X >= 10'd62 && PIXEL_COORD_X <= 10'd66 &&PIXEL_COORD_Y >= 10'd4 && PIXEL_COORD_Y <= 10'd317)begin
//			PIXEL_COLOR <= black; 
//		end
//		else if (PIXEL_COORD_X >= 10'd126 && PIXEL_COORD_X <= 10'd130 && PIXEL_COORD_Y >= 10'd4 && PIXEL_COORD_Y <= 10'd317)begin
//			PIXEL_COLOR <= black; 
//		end
//		else if (PIXEL_COORD_X >= 10'd190 && PIXEL_COORD_X <= 10'd194 && PIXEL_COORD_Y >= 10'd4 && PIXEL_COORD_Y <= 10'd317)begin
//			PIXEL_COLOR <= black; 
//		end
//		// horizontal grids for inside squares
//		else if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd62 && PIXEL_COORD_Y <= 10'd66)begin
//			PIXEL_COLOR <= black; 
//		end
//		else if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd126 && PIXEL_COORD_Y <= 10'd130)begin
//			PIXEL_COLOR <= black; 
//		end
//		else if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd190 && PIXEL_COORD_Y <= 10'd194)begin
//			PIXEL_COLOR <= black; 
//		end
//		else if (PIXEL_COORD_X >= 10'd0 && PIXEL_COORD_X <= 10'd256 && PIXEL_COORD_Y >= 10'd254 && PIXEL_COORD_Y <= 10'd258)begin
//			PIXEL_COLOR <= black; 
//		end
		else begin
			PIXEL_COLOR <=  8'b000_000_00; //black
		end
		
	 end
	 

endmodule
