module SimpleALU(
output reg [3:0] Result,
output reg C_out,

input [3:0] A, B,
input [2:0] selection 
);

// coder here

	wire [3:0] add_Result, sub_Result, com_Result, or_Result, and_Result;
	wire add_C_out, sub_C_out, com_C_out, or_C_out, and_C_out;
	
	adder A1(add_Result, add_C_out, A, B);
	subtractor S1(sub_Result, sub_C_out, A, B);
	comparator C1(com_Result, com_C_out, A, B);
//	OR O1(or_Result, or_C_out, A, B,);
//	AND AN1(and_Result, and_C_out, A, B);
	
	always @(A, B, selection)
	
		case(selection)
			3'b000: begin
						Result = add_Result;
						C_out = add_C_out;
						end
						
			3'b001: begin
						Result = sub_Result;
						C_out = sub_C_out;
						end
						
			3'b010: begin
						Result = com_Result;
						C_out = com_C_out;
						end
			
/*			3'b011: begin
						Result = and_Result;
						C_out = and_C_out;
						end
						
			3'b100: begin
						Result = or_Result;
						C_out = or_C_out;
						end
*/	
	endcase
endmodule

module adder(
output [3:0] Result,
output C_out,
input [3:0] A, B
);
// coder here

	assign {C_out, Result} = A + B;
	
endmodule

module subtractor(
output [3:0] Result,
output C_out,
input [3:0] A, B
);

// coder here

	assign {C_out, Result} = A + (~B);
	
endmodule


module comparator(
output [3:0] Result,
output C_out,
input [3:0] A, B
);
// coder here

	assign {C_out, Result} = A > B ? A : B;
	
endmodule

/*module OR(
output [3:0] Result,
output C_out,
input [3:0] A, B
);
// coder here
	assign { Result} = A or B
	
endmodule
module AND(
output [3:0] Result,
output C_out,
input [3:0] A, B
);
// coder here
	assign { Result} = A and B
	
endmodule*/
