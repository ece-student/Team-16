module RECEIVE (
	CLOCK,
	DATA,
	ENABLE,
	OUT
);

input CLOCK;
input DATA;
input ENABLE;

output [7:0] OUT;

reg [2:0] index;
reg [7:0] accumulate;
reg [7:0] pastOut;

assign OUT = pastOut;

always @(posedge CLOCK) begin
	if(ENABLE) begin
		accumulate[index] <= DATA;
		if(index == 3'b111) begin
			pastOut <= accumulate;
		end
		else begin
			pastOut <= 8'b11111111;
		end
		index <= index + 1;
	end
end
endmodule
