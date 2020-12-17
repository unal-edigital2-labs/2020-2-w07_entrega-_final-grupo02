`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.11.2020 07:38:30
// Design Name: 
// Module Name: BloquePWM
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

module bloquePWM(
                     
                   
                    output	wire pwm,
                    input	wire [2:0] orden,
					input	wire clk
                   
    );
    
   MaquinaEstadosPWM MaquinaEstadosPWM1 (
    .orden (orden),
    .clk(clk),
    .ENABLE (ENABLE),
    .reset (reset),
    .grados (grados)
   );
   
   DivFreqPWM DivisorF   (
                                  .clkin      ( clk     ),
                                  .clkout  ( clkout )
                                );
   PWM pwm1 (
          .clkpwm (clkout),
          .ENABLE (ENABLE),
          .reset (reset),
          .grados (orden),
          .pwm(pwm)
          );
endmodule


  
 
