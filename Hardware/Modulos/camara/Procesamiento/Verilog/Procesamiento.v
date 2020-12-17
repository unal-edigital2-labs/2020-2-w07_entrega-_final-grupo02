`timescale 1ns / 1ps



module imageProcess#(
		parameter AW = 15,  // Cantidad de bits  de la direcci�n
		parameter DW = 12   //tamaño de la data 
		)
		(
        clk,
        CAM_xclk,
		CAM_pclk,     //reloj 
		CAM_vsync,    //Señal Vsync para captura de datos
		CAM_href,	// Señal Href para la captura de datos
		CAM_reset,		//reset
		enable,     //señal que esperamos venga del procesador para iniciar la captura de 1 foto.
		AnchoMayor,	//Control de esctritura
		AnchoMenor,	//Dirección de memoria de entrada
		AnchoIgual,	//Data de entrada a la RAM
		CAM_px_data,
		CAM_pwdn,
		redCounter,
		greenCounter,
		blueCounter,
		nothingCounter,	
		END,
	    );
	    input clk;
	    input [7:0]CAM_px_data;
		input CAM_pclk;		//Reloj de la camara
		input CAM_vsync;	//señal vsync de la camara
		input CAM_href;		//señal href de la camara
		input CAM_reset;		//reset de la camara
		input enable;
	    output CAM_xclk;
	    output wire CAM_pwdn;	// Power down mode.
        
 		output reg [11:0] AnchoMayor;	
	    output reg [11:0] AnchoMenor;	
	    output reg [11:0] AnchoIgual;		    // Registros que indican el conteo de como es el ancho actual con respecto al ancho anterior.
        output reg [19:0] redCounter;   
        output reg [19:0] greenCounter; 
        output reg [19:0] blueCounter;  
        output reg [19:0] nothingCounter;
	    output reg END;
        
// Para la Nexys 4 con clk=100 MHz
	clk24_25_nexys4 clk25_24(
	.clk24M(CAM_xclk), //24Mhz usado para el VGA
	.clk25M(clk25M),//25Mhz usado para el VGA
	.reset(CAM_reset), // rst
	.clk100M(clk) // 100 Mhz
	);
	    
	    reg[11:0] Posy=0;
	    reg[11:0] Posx=0;
	    reg [11:0] XRGB;
	    reg [3:0] XR;
	    reg [7:0] GB;
	    
		wire clk25M;	  
	    reg count1;
	    reg count2;
	    reg imageINIT;
	    reg PixelInterested;
	    reg FilaInterested;
	    reg [11:0] AnchoActual;
        reg [11:0] AnchoAnterior; 
    
    
    
        

        reg [11:0] Errorx; //contará los errores tolerables.
        reg [11:0] Errory; //contará los errores tolerables.

        reg [11:0] ContadorFilasInterested;
        
assign CAM_pwdn = 0;			// Power down mode

       //Maquina de Estados
    localparam INIT=0,BYTE1=1,BYTE2=2,NOTHING=3,imaSiz=19199;
    
    reg [1:0]status=INIT;

   always @(posedge CAM_pclk)begin
      if(CAM_reset)begin
        status<=0; 
        end else begin  
           case (status)
              INIT: begin
                     AnchoMayor<=0;	 
                     AnchoMenor<=0;  
                     AnchoIgual<=0;  
                     AnchoActual<=0;
                     AnchoAnterior<=0;
                     greenCounter=0;
                     blueCounter=0;
                     redCounter=0;
                     nothingCounter<=0;                     
                     Errorx<=0;
                     Errory<=0;
                     Posy<=0;
                     Posx<=0;
                     END<=0;
                     count2<=0;
                     imageINIT<=0;
                     ContadorFilasInterested<=0;       
                   if(CAM_vsync&~CAM_href)begin // Cuando Vsync es 1, significa que una nueva imagen está por capturarse
                     status<=BYTE1;
                         end else 
                     status<=INIT;                   
                end
              BYTE1: begin
                   if(~CAM_vsync&CAM_href)begin// Cuando Vsync se hace 0 y tenemos el primer href podemos asumir que tenemos el primer dato de fila, con el BYTE2 "procesamos" la fila
                     status<=BYTE2;            
                     Posy<=Posy+1;              //comenzamos una nueva fila
                     Posx<=Posx+1;              //El primer Href detectado viene acompañado del primer byte
                     XR<=CAM_px_data[3:0];
                     count1<=0; //auxiliar
                     PixelInterested<=0;//auxiliar
                     Errorx<=0;
                     FilaInterested<=0;
                     AnchoActual<=0;

                     imageINIT<=1;//flag que dice si ya se comenzó la captura
                     end else if ((CAM_vsync&~CAM_href)&&imageINIT) begin               
                
                     END<=1;
                     status<=NOTHING;    // si volvemos a detectar un Vsync quiere decir que acabamos la foto.
                     end else
                             status<=BYTE1;
               end
              BYTE2: begin
                   if(~CAM_vsync&~CAM_href) begin// cuando las dos estén apagadas quiere decir que vamos a cambiar de fila
                   
                   // Antes de cambiar de fila queremos notar si la fila ya procesada  es de nuestro interes
                        if(FilaInterested&~count2) begin          
                          AnchoAnterior<=AnchoActual; 
                          count2<=2'b1;  //count2 es como un flag que me indica cuando ya hay alguna fila que tenga valores de interes
                          ContadorFilasInterested<=ContadorFilasInterested+1;//cuenta cuantas filas de interes llevamos
                    
                           end else if((FilaInterested&count2)&&Errory<3) begin  //Si entra acá significa que ya una fila anterior resultó ser de interes, ahora necesitamos comparar dicha fila anterior con la procesada actualmente 
                                  //Determinación de salidas 
                                       if((AnchoActual)<(AnchoAnterior-1)) 
                                             AnchoMenor=AnchoMenor+1;
                                         else if((AnchoActual)>(AnchoAnterior+1)) // los numeros sumados y restados permiten cierto margen de error (de 3 pixeles)
                                             AnchoMayor=AnchoMayor+1;
                                          else if((AnchoAnterior==AnchoActual)||((AnchoActual-1)==AnchoAnterior)||((AnchoActual+1)==AnchoAnterior))//((AnchoActual-2)==AnchoAnterior)||((AnchoActual+2)==AnchoAnterior)) 
                                             AnchoIgual=AnchoIgual+1;
                                  
                                            AnchoAnterior=AnchoActual;
                                          
                                            Errory=0;
                                            count2=1;
                       
                    end else if(~FilaInterested&count2) begin //cuando no encuentre una fila de interes, pero count 2 ya haya sido activado, significa que hay un miss en y.
                                  Errory=Errory+1;
                    end
                  // 
                   if(Errory<7)begin
                   status<=BYTE1;    // vuelve al BYTE1 que nos detecta cuando nos da el primer pixel de la siguiente fila fila
                   Posx<=0;end
                   else begin
                   end 
                   
                   
                      end else if(CAM_href) begin // Href activo indica que estamos en una fila
        ////////////////////////////////////////////////////////////////////////////////////////////////procesamiento fila                  
                          //Distinsión de color
                                  if(~count1)begin
                                    GB=CAM_px_data;
                                    XRGB={XR,GB}; //Ahora que tenemos el pixel completo definimos el color.
                                         
                                  if((XRGB[11:8]>14)||(XRGB[7:4]>14)||(XRGB[3:0]>14))begin
                                         
					  if(XRGB[11:8]>12)begin //para que la imagen se vea roja, tiene que ser mucho mayor a los otros dos componentes 
                                          redCounter=redCounter+1;                                   //Con que sea + de 5 tendra un tono bastante rojo.
                                          PixelInterested=1; 
                                          end else 
                                          redCounter=redCounter;
                                          
					  if(XRGB[7:4]>12)begin  //lo mismo para los demas colores
                                          greenCounter=greenCounter+1;
                                          PixelInterested=1;
                                          end else 
                                          greenCounter=greenCounter;
                                          
					  if(XRGB[3:0]>12)begin 
                                          blueCounter=blueCounter+1;
                                          PixelInterested=1;
                                          end else 
                                          blueCounter=blueCounter;
                                          
                                    end else begin
                                    PixelInterested=0; //Si es del color solicitado estamos interesados, de lo contrario ponemos 0 en esta variable.
                                    nothingCounter=nothingCounter+1;
                                    end        
                                         
                                    count1<=~count1; //Me ayuda a que en el siguiente ciclo guarde el XR
                                  end 
                                  else if(count1)begin
                                    XR<=CAM_px_data;
                                    count1<=~count1; //Me ayuda a que en el siguiente ciclo guarde el GB
                                    PixelInterested=1'bz; //De esta manera no se procesa el pixel cuando no está completo.
                                  end
                      
                      // Si ya sabemos que es un pixel de nuestro interes vamos a hallar que ancho tiene ese color de nuestro interes.
                                  
                                      if(PixelInterested&&Errorx<2)begin  //Si encontramos un pixel de interes y los errores consecutivos son menores a 4 sumamos 1 ancho.
                                         AnchoActual<=1+AnchoActual;
                                         Errorx<=0;//si encontramos pixel de interes vuelve a 0 el error     
                                          
                                     end else if(~PixelInterested&&AnchoActual>0) //Cuando encontramos que no hay pixel de interes y además ya habiamos encontrado un  pixel de nuestro interes tenemos un error
                                        Errorx<=Errorx+1;
                                    
                                    
                                     if(AnchoActual>3)             //Si tenemos más de 2 pixeles consecutivos que sean de nuestro interes, decimos que la fila es de nuestro interes
                                              FilaInterested=1;
                                        else  
                                              FilaInterested=0;
                                             
                     

                   ///////////////////////////////////////////////////////////////////////////////////////Fin de procesamiento
                   //Conteo
                   Posx<=Posx+1; //si estamos en la fila, podemos decir que cada pclk representa un byte
                   //2bytes representan 1 pixel.
                   end
                   else 
                    status<=BYTE2;
              end
               NOTHING: begin
                  //if(enable) status<=0; // si hay enable vuelve a buscar foto
                  //else  
                  END<=1;
                        end
           endcase
      end
   end
     
       
endmodule
