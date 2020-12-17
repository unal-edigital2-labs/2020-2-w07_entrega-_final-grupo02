`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.11.2020 08:35:50
// Design Name: 
// Module Name: PWM
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


module PWM#(
parameter top=400)  //20ms con el clk
( 
  output reg pwm=0,
  input  [1:0] grados, 
  input ENABLE,
  input reset,
  input clkpwm
    );
reg [10:0] contador;
reg [7:0] ancho;
initial
begin
contador=0;
ancho=30;
end
	always@(posedge clkpwm)
    begin 
      
    if(reset==1)begin 
    contador=0; end
    
 if(ENABLE==1)
  begin  
        contador<=contador+1;
    
  
        if(grados==2'b00) begin
         ancho<=30; end               //numero de ciclos de reloj para hacer 1.5ms
        else if(grados==2'b01) begin
         ancho<=50; end                //numero de ciclos de reloj para hacer 2ms
        else if(grados==2'b10) begin
         ancho<=10; end                //numero de ciclos de reloj para hacer 1ms
        else begin
         ancho<=30; end 
         
        //Creación del pulso modulado      
        if(contador<ancho) begin 
        pwm<=1; end
        else if(contador>=ancho) begin
        pwm<=0; end 
        else  begin
        pwm<=0; end
    
        if(contador>=top-1)begin 
        contador<=0; end
                                                       
  end  
    
end    
endmodule
