
module DivFreqPWM#( 
parameter top=12'h9C4) //100M/20k =5k  (para que nuestro clock sea de 20khz)
    (input clkin,
    output reg clkout
    );
    reg [12:0] count_D;
	
	initial
	begin
		clkout=1'b1;
		count_D=0;
	end
	
	always @(posedge clkin) 
	begin
		count_D <= count_D + 1;
		if(count_D == top-1)
		begin
			count_D<=0;
			clkout <= ~clkout;
		end
	end
endmodule
