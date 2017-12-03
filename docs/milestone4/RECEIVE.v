module RECEIVE (
	CLOCK,
	DATA,
	ENABLE,
	OUT
);

input CLOCK;
input DATA;
input ENABLE;

output [15:0] OUT;

reg [3:0] index;
reg [15:0] accumulate;
reg [15:0] pastOut;

assign OUT = pastOut;

always @(posedge CLOCK) begin
	if(ENABLE) begin
		accumulate[index] <= DATA;
		if(index == 4'b1111) begin
			pastOut <= accumulate;
		end
		else begin
			pastOut <= 16'b1111100000000000;
		end
		index <= index + 1;
	end
end
endmodule
