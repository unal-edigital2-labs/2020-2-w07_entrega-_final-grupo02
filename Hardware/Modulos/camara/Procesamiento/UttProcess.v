`timescale 10ns / 1ns
module UttProcess;

	// Inputs. Declare as reg because are in left part of initial statemet.
	reg clk;
	reg CAM_reset;
	reg pclk;
	reg CAM_vsync;
	reg CAM_href;
	reg [7:0] CAM_px_data;


	// Outputs
	wire CAM_xclk;
	wire CAM_pwdn;
	//wire [15:0] AnchoMayor;	
    //wire [15:0] AnchoMenor;	
	//wire [15:0] AnchoIgual;	
wire  AnchoMayor;
wire  AnchoMenor;
wire  AnchoIgual;
wire  END;
 
    // Senales de prueba ******************************
// Absolute Address in Esteban's computer

// Absolute address in Niko's computer
// localparam d="C:/Users/LucasTheKitten/Desktop/Captura/wp2-simulacion-captura-grupo-03/src/test_vga.txt";	
// Absolute address in Niko's mac computer
// localparam d="C:/Users/Nikolai/Desktop/wp2-simulacion-captura-grupo-03/src/test_vga.txt";	
	// Instantiate the Unit Under Test (UUT)
	imageProcess uut (
		.clk(clk),
		.CAM_reset(CAM_reset),
		.CAM_xclk(CAM_xclk),
		.CAM_pwdn(CAM_pwdn),
		.CAM_pclk(pclk),
		.CAM_vsync(CAM_vsync),
		.CAM_href(CAM_href),
	    .AnchoMayor(AnchoMayor),
	    .AnchoMenor(AnchoMenor),
	    .AnchoIgual(AnchoIgual),
		.CAM_px_data(CAM_px_data),
		.END(END)
	
    );
	reg img_generate=0;
	
	
	initial begin // Do at start of test. 
		// Initialize Inputs
		clk = 0;
		CAM_reset = 1;				// Press rst.
		pclk = 0;
		CAM_vsync = 1;			// Empieza la imagen.
		CAM_href = 0;			// Empieza la imagen.
		CAM_px_data = 8'h0f;	// Red
   	// Wait 100 ns for global reset to finish
		#20;
		CAM_reset = 0; 				// registros en fisico para que reinicialicen.
		// #1_000_000;			// se puede quitar en simulacion, estoy esperando que la memoria se llene.
		img_generate=1;			// Estaban pegados
	end

	//Reloj de 100 kHz
	//always #0.5 clk  = ~clk; // Cada 1 unidad de tiempo cambia a su estado opuesto, proporcionando un un relo.

	//Reloj de 50 kHz
	always #1 clk  = ~clk; // Cada 1 unidad de tiempo cambia a su estado opuesto, proporcionando un un relo.
	
 	always #2 pclk  = ~pclk;


	reg [8:0]line_cnt=0;   //2^9-1=511, TAM_LINE+BLACK_TAM_LINE=324  
	reg [6:0]row_cnt=0;    //2^7-1= 127, TAM_ROW+BLACK_TAM_ROW=124 

	parameter TAM_LINE=320;	// 160x2 debido a que son dos pixeles de RGB
	parameter TAM_ROW=120;
	parameter BLACK_TAM_LINE=4;
	parameter BLACK_TAM_ROW=4;
	
	/*************************************************************************
			INICIO DE SIMULACION DE SE�ALES DE LA CAMARA
	**************************************************************************/


// Color rojo.

/*
reg cont=0;   
    initial forever  begin
		@(negedge pclk) begin
            if(cont==0) begin 
                CAM_px_data<=8'h0f;		// First byte red.
            end
            else begin
                CAM_px_data<=8'h00;		// Second byte 
            end
			cont=cont+1;
         end
	end

/*

// blue.
reg [2:0]cont=0;   

    initial forever  begin
		@(negedge pclk) begin
            if(~CAM_href) cont=0;			

            if(cont==0|cont==2) begin		
                CAM_px_data<=8'h0;
            end
            else if(cont==1|cont==3) begin	
                CAM_px_data<=8'h0f;
            end
            else if(cont==4|cont==6) begin	
                CAM_px_data<=8'h00;
            end
            else if(cont==5|cont==7) begin	
                CAM_px_data<=8'h0f;
            end
			cont=cont+1;
         end
	end
*/
	
//VERDE
reg [2:0]cont=0;   

    initial forever  begin
		@(negedge pclk) begin
            if(~CAM_href) cont=0;			

            if(cont==0|cont==2) begin		
                CAM_px_data<=8'h0;
            end
            else if(cont==1|cont==3) begin	
                CAM_px_data<=8'hf0;
            end
            else if(cont==4|cont==6) begin	
                CAM_px_data<=8'h00;
            end
            else if(cont==5|cont==7) begin	
                CAM_px_data<=8'hf0;
            end
			cont=cont+1;
         end
	end
//Triangulo 
    /*reg cont=0;   
    reg [11:0]contador=0;
    reg filasFlag=0;
    reg [11:0]FilasCounter=0;
    initial forever  begin
		@(negedge pclk) begin
            if(~CAM_href&CAM_vsync) begin 
              cont<=0;			
              contador<=0;
              CAM_px_data<=8'h0;
              FilasCounter<=0;
 end
          
           if(~CAM_href&~CAM_vsync&filasFlag)begin
            FilasCounter<=FilasCounter+4;
            filasFlag<=0;
            contador<=0;
            CAM_px_data<=8'h0;
           end
            
           
         if(CAM_href&~CAM_vsync)begin
          if(contador<FilasCounter)begin
            if(~cont) begin		
                CAM_px_data<=8'h0;
            end
            else if(cont) begin	
                CAM_px_data<=8'h0f;
            end
          end else  CAM_px_data<=8'h0;
          
			cont<=cont+1;
		    contador<=contador+1;
            filasFlag<=1;         
          end
	end
end*/
	
	/* Simulacion de contador de pixeles para generar Href y vsync. */

	/*
	reg [2:0]cont=0;   

    initial forever  begin
		@(negedge pclk) begin
            if(~CAM_href) cont=0;			

            if(cont==0|cont==2) begin		
                CAM_px_data<=8'h0;
            end
            else if(cont==1|cont==3) begin	
                CAM_px_data<=8'h0f;
            end
            else if(cont==4|cont==6) begin	
                CAM_px_data<=8'h00;
            end
            else if(cont==5|cont==7) begin	
                CAM_px_data<=8'h0f;
            end
			cont=cont+1;
         end
	end
	*/
	initial forever  begin
	    //CAM_px_data=~CAM_px_data;
		@(posedge pclk) begin
		if (img_generate==1) begin	// Mientras se genere una imagen.
			line_cnt=line_cnt+1;	// Cada pclk aumenta line_cnt.
			if (line_cnt >TAM_LINE-1+BLACK_TAM_LINE) begin	// Termina una fila.
				line_cnt=0;									// Reinicia contador.
				row_cnt=row_cnt+1;							// Aumenta numero de fila.
				if (row_cnt>TAM_ROW-1+BLACK_TAM_ROW) begin	// Termina de recorrer todas las filas.
					row_cnt=0;								// Empieza de nuevo.
				end
			end
		end
		end
	end

	/*simulaci�n de la se�al vsync generada por la camara*/
	initial forever  begin
		@(posedge pclk) begin
            if (img_generate==1) begin
                    if (row_cnt==0)begin	// Antes del delay previo a la primera fila, no comparte. 
                        CAM_vsync  = 1;
                    end
                if (row_cnt==BLACK_TAM_ROW/2)begin
                    CAM_vsync  = 0;			// row_cnt = 2, luego del delay, empieza a compartir.
                end
            end
		end
	end

	/*simulaci�n de la se�al href generada por la camara*/
	initial forever  begin
		@(negedge pclk) begin
            if (img_generate==1) begin
                if (row_cnt>BLACK_TAM_ROW-1)begin // Como es negedge. Ya paso dos posedge, parte negra antes compartir href.
                    if (line_cnt==0)begin
                        CAM_href  = 1;			  // Empieza fila.
                    end
                end
                if (line_cnt==TAM_LINE)begin
                    CAM_href  = 0;				// debe empezar nueva fila.
                end
            end
		end
	end

	
    
	

endmodule