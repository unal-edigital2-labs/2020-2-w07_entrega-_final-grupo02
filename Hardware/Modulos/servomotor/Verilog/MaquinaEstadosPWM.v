`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.11.2020 07:32:42
// Design Name: 
// Module Name: MaquinaEstadosPWM
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
              
module  MaquinaEstadosPWM  (
                            input clk,
                            input	[2:0] orden,
                            output	reg	ENABLE,
                            output	reg	reset,
                            output  reg [1:0] grados
                          );
	always@(posedge clk)
	begin
	case(orden[2])
		1'b1:	
		begin
			ENABLE <=  1;
	      	reset  <=  0;
		end
		1'b0:
		begin
			reset  <=  1;
	     		ENABLE <=  0;
		end
		default:
		begin
			reset  <=  0;
	     		ENABLE <=  0;
		end
	endcase
	
		case({orden[1],orden[0]})
		2'b00:	
		begin
			grados <=  0; //00 van a ser 0grados
	      	
		end
		2'b01:
		begin
			grados <=  1;  //01 van a ser 90grados
		end
		
		2'b10:
		begin

			grados <=  2;  //10 van a ser -90grados
		end
		
		default:
		begin 	

			grados<=  2'b00;   //11 va a ser un indicador de error
		end
	endcase
	
	end
endmodule
