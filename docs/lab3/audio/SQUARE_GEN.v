//Clock runs at 25MHz

module SQUARE_GEN (
	CLOCK,
	RESET,
	FREQ,
	OUT
);

input CLOCK;
input RESET;
input [19:0] FREQ; // Equal to 25MHz / (2 * desired frequency)

output [7:0] OUT;

reg [19:0] counter; // The counter is used to time the square wave
reg [7:0] pastOut;

assign OUT = pastOut;

always @(posedge CLOCK) begin
	if (RESET) begin
		pastOut <= 8'b00000000;
		counter <= FREQ;
	end
	else if ((counter < 1) && (~pastOut[0])) begin
		counter <= FREQ;
		pastOut <= 8'b11111111;
	end
	else if ((counter < 1) && (pastOut[0])) begin
		counter <= FREQ;
		pastOut <= 8'b00000000;
	end
	else begin
		counter <= counter - 1;
	end
end	
endmodule
