//Clock runs at 25MHz

module TUNE_GEN (
	CLOCK,
	RESET,
	DONE,
	FREQ1,
	FREQ2,
	FREQ3,
	TIME,
	OUT
);

input CLOCK;
input RESET;
input DONE;
input [31:0] TIME;
input [19:0] FREQ1; // Equal to (25MHz / (256 * desired frequency)) -1
input [19:0] FREQ2; // Equal to (25MHz / (256 * desired frequency)) -1
input [19:0] FREQ3; // Equal to (25MHz / (256 * desired frequency)) -1

output [7:0] OUT;

reg doneReg;
reg [19:0] counter1; // The counter is used to time frequency 1
reg [19:0] counter2; // The counter is used to time frequency 2
reg [19:0] counter3; // The counter is used to time frequency 3
reg [19:0] counter4;
reg [31:0] duration; // time duration of note played
reg [7:0] pastOut;

wire [7:0] outPass;

assign outPass = pastOut;
assign OUT = outPass;

localparam STATE_Initial = 3'b000, //pre-DONE signal
	STATE_1 = 3'b001, // Low E
	STATE_2 = 3'b010, // Low E
	STATE_3 = 3'b011, // Low F
	STATE_4 = 3'b100; // Low D
	
reg[2:0] currState;
reg[2:0] nextState;

reg[3:0] iterations;

always @(posedge CLOCK) begin
	if (RESET) begin
		pastOut <= 8'b00000000;
		counter1 <= FREQ1;
		counter2 <= FREQ1;
		counter3 <= FREQ2;
		counter4 <= FREQ3;
		iterations <= 4'b0100;
		currState <= STATE_Initial;
	end
	else if(DONE) begin
		doneReg <= DONE;
		nextState <= STATE_1;
		doneReg <= 1'b0;
	end
	else begin
		currState <= nextState;
		case(currState)
			STATE_Initial: begin
				nextState <= STATE_Initial;
			end
			
			STATE_1: begin
				if(counter1 < 1) begin
					counter1 <= FREQ1;
					pastOut <= pastOut + 1;
				end
				else begin
					counter1 <= counter1-1;
				end
				
				if(duration<1)begin
					nextState <= STATE_2;
					duration <= TIME;
				end
				else begin
					nextState <= STATE_1;
					duration <= duration-1;
				end
			end
			
			STATE_2: begin
				if(counter2 < 1) begin
					counter2 <= FREQ1;
					pastOut <= pastOut + 1;
				end
				else begin
					counter2 <= counter2-1;
				end
				if(duration<1)begin
					nextState <= STATE_3;
					duration <= TIME;
				end
				else begin
					nextState <= STATE_2;
					duration <= duration-1;
				end
			end
			
			STATE_3: begin
				if(counter3 < 1) begin
					counter3 <= FREQ2;
					pastOut <= pastOut + 1;
				end
				else begin
					counter3 <= counter3-1;
				end
				if(duration<1)begin
					nextState <= STATE_4;
					duration <= TIME;
				end
				else begin
					nextState <= STATE_3;
					duration <= duration-1;
				end
			end
			
			STATE_4: begin
				if(counter4 < 1) begin
					counter4 <= FREQ3;
					pastOut <= pastOut + 1;
				end
				else begin
					counter4 <= counter4-1;
				end
				if(duration<1)begin
					nextState <= STATE_Initial;
					duration <= TIME;
				end
				else begin
					nextState <= STATE_4;
					duration <= duration-1;
				end
			end
			
		endcase
	end
//	else if (counter < 1) begin
//		counter <= FREQ;
//		pastOut <= pastOut + 1;
//	end
//	else begin
//		counter <= counter - 1;
//	end
end	
endmodule
