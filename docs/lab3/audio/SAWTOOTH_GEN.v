//Clock runs at 25MHz

module SAWTOOTH_GEN (
	CLOCK,
	RESET,
	FREQ,
	OUT
);

input CLOCK;
input RESET;
input [19:0] FREQ; // Equal to (25MHz / (256 * desired frequency)) -1

output [7:0] OUT;


reg [19:0] counter; // The counter is used to time the square wave
reg [7:0] pastOut;

assign OUT = pastOut;

always @(posedge CLOCK) begin
	if (RESET) begin
		pastOut <= 8'b00000000;
		counter <= FREQ;
	end
	else if (counter < 1) begin
		counter <= FREQ;
		pastOut <= pastOut + 1;
	end
	else begin
		counter <= counter - 1;
	end
end	
endmodule
