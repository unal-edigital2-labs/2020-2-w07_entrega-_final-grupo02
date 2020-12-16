
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>
#include "delay.h"
#include "display.h"



static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}
	return NULL;
}

//PRUEBA DE MODULOS//////////////////////////////PRUEBA DE MODULOS//////////////////////////////////////////PRUEBA DE MODULOS/////////////////////////// 

//PRUEBA DE MODULOS//////////////////////////////PRUEBA DE MODULOS//////////////////////////////////////////PRUEBA DE MODULOS///////////////////////////

//PRUEBA DE MODULOS//////////////////////////////PRUEBA DE MODULOS//////////////////////////////////////////PRUEBA DE MODULOS///////////////////////////

//PRUEBA DE MODULOS//////////////////////////////PRUEBA DE MODULOS//////////////////////////////////////////PRUEBA DE MODULOS///////////////////////////

//PRUEBA DE MODULOS//////////////////////////////PRUEBA DE MODULOS//////////////////////////////////////////PRUEBA DE MODULOS///////////////////////////

//PRUEBA DE MODULOS//////////////////////////////PRUEBA DE MODULOS//////////////////////////////////////////PRUEBA DE MODULOS///////////////////////////

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                                - this command");
	puts("reboot                              - reboot CPU");
	puts("led                                 - led test");
	puts("switch                              - switch test");
	puts("motor                               - motor test");
	puts("US                                  - ultrasonido test");
	puts("Cam                                 - procesamiento test");
	puts("uart1                               - Comunicacion arduino test");
	puts("uart2                               - Comunicacion bluetooth test");
	puts("infra                               - Prueba de infrarrojos");
//      puts("\n  //////////////////////////////////////////////\n")
	puts("\ninit                              - Iniciar software del robot\n");
	

}
static void bhelp(void)
{
	puts("\nPresione 1 para continuar con el siguiente paso\n");

}


static void reboot(void)
{
	ctrl_reset_write(1);
}


static void led_test(void)
{/*
	unsigned int i;
	printf("Test del los leds... se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) { //No hay interrupción, espera todo el tiempo para interrumpir.

	for(i=1; i<65536; i=i*2) {
		leds_out_write(i);
		delay_ms(50);
	}
	for(i=32768;i>1; i=i/2) {
		leds_out_write(i);
		delay_ms(50);
	}
	}
 */	
}


static void switch_test(void)
{/*
	printf("Test del los interruptores... se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {

    leds_out_write(switchs_in_read());         
		
		
	}*/
}





static void motor_test(void)
{  /*
	unsigned int i;
	printf("Test del motor se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {
	
	for(i=4; i<7; i=i+1) {
		pwm_cntrl_orden_write(i);
		delay_ms(700);
	   printf("se está enviando %i \n", i);

	}
	for(i=5;i>4; i=i-1) {
		pwm_cntrl_orden_write(i);
		delay_ms(700);
	    printf("se está enviando %i \n", i);

	}
	}*/
}


static void US_test(void)
{ /*
	unsigned int i;
	printf("Test del ultrasonido se interrumpe con el botton 1 e inicia con el boton 2\n");
	while(!(buttons_in_read()&1)) {
	if(buttons_in_read()&2){
	  US_cntrl_orden_write(1);
	   if(US_cntrl_DONE_read()){
	     i=US_cntrl_d_read();
	     printf("La distancia del US a la siguiente pared es de: %i", i);
	     printf("cm 1\n");
         delay_ms(500);}
	 }else{
	US_cntrl_orden_write(0);
	 }
	}*/
}



static void Process_test(void)
{ /*  
	 unsigned int a,b,c,g;
	 unsigned int d,e,f;
	printf("Test del procesamiento se interrumpe con el botton 1\n");
	while(!(buttons_in_read()&1)) {
	 if((buttons_in_read()&2)){
	  Process_cntrl_CAM_reset_write(1);
	  Process_cntrl_CAM_reset_write(0);
      delay_ms(200);
	   if(Process_cntrl_END_read()){
	     a=Process_cntrl_AnchoIgual_read();
		 printf(" El contador de ancho igual fue : %i", a);	     
		 b=Process_cntrl_AnchoMayor_read();
		 printf("\n \n  El contador de ancho mayor fue  : %i", b);
		 c=Process_cntrl_AnchoMenor_read();
		 printf("\n  El contador de ancho menor fue  : %i", c);
         d=Process_cntrl_redCounter_read();
		 printf("\n  pixeles rojos contados  : %i", d);
		 e=Process_cntrl_greenCounter_read();
		 printf("\n  pixeles verdes contados  : %i", e);
		 f=Process_cntrl_blueCounter_read();
		 printf("\n  pixeles azules contados  : %i", f);
		 g=Process_cntrl_nothingCounter_read();
		 printf("\n  NothingPixel contados  : %i", g);
		printf("\n  FIN \n");
	 delay_ms(300);
	   }
	 
	  }
	}
*/}



static void Uart1_test(void)

{	/*printf("Test de la uart 1, debe poner en corto el pon RX Tx de la la UART2.\n");
	 for(int i=1;i<=10;i++){
		printf("ENTRE\n");
		uart1_rxtx_write('Y');
		delay_ms(500);
		uart1_rxtx_write('N');
		delay_ms(500);
	}*/
}

static void Uart2_test(void)
{ /*printf("Test de la uart 2, debe poner en corto el pon RX Tx de la la UART2.\n");
	 for(int i=1;i<=200;i++){
		printf("ENTRE\n");

		uart2_rxtx_write('R');
		uart2_rxtx_write('O');
		uart2_rxtx_write('B');
		uart2_rxtx_write('O');
		uart2_rxtx_write('T');
		uart2_rxtx_write('D');
		uart2_rxtx_write('I');
		uart2_rxtx_write('G');
		uart2_rxtx_write('I');
		uart2_rxtx_write('T');
		uart2_rxtx_write('A');
		uart2_rxtx_write('L');
		uart2_rxtx_write('2');
		uart2_rxtx_write(' ');
		uart2_rxtx_write('B');
		uart2_rxtx_write('T');
		uart2_rxtx_write(' ');		


		

		delay_ms(50);
		}
*/
}



static void Infra_test(void)
{ 
/*
	bool infra1 =0;
	bool infra2 =0;
	bool infra3 =0;
	bool mov=1;
	printf("Test de infrarojos... se interrumpe con el botton 1\n");
	while(mov) {
		 if (infrarrojos_in_read()&1){
		  infra1=1;
		 }else { infra1=0; }
		 if (infrarrojos_in_read()&2){
		  infra2=1;
		 }else { infra2=0; }
		 if (infrarrojos_in_read()&4){
		  infra3=1;		  
		 }else { infra3=0; }

	   printf("resultado del text:\n");
	   printf("infrarojo 1: %i\n",infra1);
	   printf("infrarojo 2: %i\n",infra2);
	   printf("infrarojo 3: %i\n",infra3);

    if(infra1&infra2&infra3){ //cuando todos los infrarojos detectén negro
		mov=0;
	//  UART1()---------------------->enviar mov al arduino		
		printf("\n*Detenido*(3 infra detectados)\n");
	}else if(infra2){ //cuando solo el infrarojo del centro este encendido hay movimiento
        mov=1;
		printf("\n*MOVIENDOSE*(solo 1 infra detectado)\n");
	//  UART1()---------------------->enviar mov al arduino
		delay_ms(1000);
	}else{
		printf("\nEl infrarojo se salió del camino\n");
		delay_ms(1000);

	}
  }*/
}

static bool console_service(bool init)
{
	char *str;
	char *token;

if(!init){
	str = readstr();
	if(str == NULL) return 0;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0){
		reboot(); return 0;}
	else if(strcmp(token, "led") == 0){
		led_test(); return 0;} 
	else if(strcmp(token, "switch") == 0){
		switch_test(); return 0;}
	else if(strcmp(token, "motor") == 0){
		motor_test(); return 0;}	
	else if(strcmp(token, "US") == 0){
		US_test(); return 0;}	
	else if(strcmp(token, "Cam") == 0){
		Process_test(); return 0;}	
    else if(strcmp(token, "uart1") == 0){
		Uart1_test(); return 0;}	
	else if(strcmp(token, "Pr") == 0){
		ImageProcess(); return 0;}	
	else if(strcmp(token, "infra") == 0){
		Infra_test(); return 0;}
	else if(strcmp(token, "init") == 0){
		return 1;}			
	prompt();
	}else{
	str = readstr();
	if(str == NULL) return 0;
	token = get_token(&str);
	if(strcmp(token, "1") == 0)
		return 1;
	else{
		return 0;
	}			

	}
}
//Mapa//////////////////////////////Mapa//////////////////////////////////////////Mapa///////////////////////////Mapa

//Mapa//////////////////////////////Mapa//////////////////////////////////////////Mapa///////////////////////////Mapa

//Mapa//////////////////////////////Mapa//////////////////////////////////////////Mapa///////////////////////////Mapa

//Mapa//////////////////////////////Mapa//////////////////////////////////////////Mapa///////////////////////////Mapa

//Mapa//////////////////////////////Mapa//////////////////////////////////////////Mapa///////////////////////////Mapa

//Mapa//////////////////////////////Mapa//////////////////////////////////////////Mapa///////////////////////////Mapa


struct { char paredArriba[3]; char paredIzq[3]; char paredDer[3];char paredAbajo[3]; bool DONE; short Anterior[2]; } Map[16] = {
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos0 del string, 11 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos1 del string, 12 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos2 del string, 13 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos3 del string, 14 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos4 del string, 21 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos5 del string, 22 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos6 del string, 23 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos7 del string, 24 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos8 del string, 31 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos9 del string, 32 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos10 del string, 33 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos11 del string, 34 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos12 del string, 41 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos13 del string, 42 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos14 del string, 41 de la matriz
  {'N','N','N'}, {'N','N','N'},{'N','N','N'},{'N','N','N'},0,{0,0},   //pos15 del string, 40 de la matriz
};
    
   //Primer caracter me indicará si hay figura Y:HAY, N:no hay 
   //Segundo caracter indicara el color Azul:A Verde:V Rojo:R, N:Nada
   //Tercer caracter la figura S:square, C:circle, T:triangle,N:Nada
   //El done me indica si ya se caracterizó ese punto
   //desicion[0] me dirá de donde vino el robot
   //desicion[1] de dirá con que orientacion vino
    
  

    short contTotal;
	short PosAnterior=0;
	short orientacion; //hacia donde está mierando el robot? 0 adelante,1 derecha,2 izquierda,3 atras.
    short orientacionAnterior=0;
	char Figura='N';
	char Color='N';

///////////////////////////////////////////////FUNCIONES DE CARACTERIZAR PUNTO////////////////////////////////////////////////////////

///////////////////////////////////////////////FUNCIONES DE CARACTERIZAR PUNTO////////////////////////////////////////////////////////

///////////////////////////////////////////////FUNCIONES DE CARACTERIZAR PUNTO////////////////////////////////////////////////////////

///////////////////////////////////////////////FUNCIONES DE CARACTERIZAR PUNTO////////////////////////////////////////////////////////

char FiguraD(short Menor,short Mayor,short Igual){
char figuraD='N';
     if(((Mayor>(Menor+1))&&(Mayor>(Igual+1)))||((Menor>(Mayor+1))&&(Menor>(Igual+1)))){
	   figuraD='T';  
                            
	 }else if((Igual>(Menor+1))&&(Igual>(Mayor+1))){
	   figuraD='S';

	 }else if((Mayor==Menor)&&((Mayor+1)==Menor)&&((Mayor-1)==Menor)){
	   figuraD='C';
     	   	   
	 }else{
	   figuraD='N';
  	   	   
	}

return figuraD;	
}

char ColorD(short blue,short green,short red,short nothing){
char colorD='N';
if(nothing>22000||(blue<1000&&green<1000&&red<1000)){ return 'N';}else{
     if((blue>green)&&(blue>red)){
	   colorD='A';  
                
	 }else if((green>blue)&&(green>red)){
	   colorD='V';

	 }else if((red>green)&&(red>blue)){
	   colorD='R';
     	   	   
	 }else{
	   colorD='N';
  	   	   
	}
	}

return colorD;
}
void ImageProcess(void)
{
	 unsigned short NoColor,colorAzul,colorVerde,colorRojo,d,e,f,g;
	 unsigned short Square,Circle,Triangle,NoFigure;
	 colorAzul=0;
	 colorVerde=0;
	 colorRojo=0;
	 NoColor=0;
	 NoFigure=0;
	 Square=0;
	 Circle=0;
	 Triangle=0;
	 Figura='N';
	 Color='N';
	 bool END=0;
	 bool ctrl=0;
	 char color='N';
	 char figura='N';	 
	 bool flagDone=0;


printf("\nPresione 1 cuando este listo para tomar la foto\n");
   while(!END){ 
	   ctrl=console_service(1);	
	   if(ctrl){  
       END=1;
	  Process_cntrl_enable_write(1);
	  for(short i=0;i<15;i++){  //Tomara 500fotos;
	  Process_cntrl_CAM_reset_write(1);
	  delay_ms(50);
	  Process_cntrl_CAM_reset_write(0);
      flagDone=0;
	  while(!flagDone){	  		  
	   if(Process_cntrl_END_read()){
	     d=Process_cntrl_redCounter_read();
		 printf("\n  pixeles con más de 12 en rojo contados  : %i", d);
		 e=Process_cntrl_greenCounter_read();
		 printf("\n  pixeles con más de 12 en verde contados  : %i", e);
		 f=Process_cntrl_blueCounter_read();
		 printf("\n  pixeles con más de 12 en azul contados  : %i", f);
		 g=Process_cntrl_nothingCounter_read();
		 printf("\n  NothingPixel contados  : %i", g);
                printf("\n ");
		 
		 color=ColorD(f,e,d,g);
         figura=FiguraD(Process_cntrl_AnchoMenor_read(),Process_cntrl_AnchoMayor_read(),Process_cntrl_AnchoIgual_read());      
	     
		 if(color=='A'){colorAzul=colorAzul+1;}
		 else if(color=='V'){colorVerde=colorVerde+1;}
		 else if(color=='R'){colorRojo=colorRojo+1;}
		 else if(color=='N'){NoColor=NoColor+1;}
		
		 
	     if(figura=='S'){Square=Square+1;}
		 else if(figura=='C'){Circle=Circle+1;}
		 else if(figura=='T'){Triangle=Triangle+1;}
		 else if(figura=='N'){NoFigure=NoFigure+1;}
		 

	   flagDone=1;
       delay_ms(5);
	   }else{flagDone=0;
	   }
	 }
	}
		 printf("\n Luego de tomar 500 fotos el robot estimó:");	     
     
	 if(NoColor>200){
	  Color='N';
	 }else if((colorAzul>=colorVerde)&&(colorAzul>=colorRojo)){
      Color='A';
	 }else if((colorVerde>=colorAzul)&&(colorVerde>=colorRojo)){
      Color='V';
     }else if((colorAzul>=colorVerde)&&(colorAzul>=colorRojo)){
	  Color='A';
	 }

     if(NoFigure>200&&NoColor>200){
      printf("No figura identificada");
	   Figura='N';
	 }else if((Triangle>=Square)&&(Triangle>=Circle)){
	   Figura='T';  
	   printf("\n La figura puede ser un triangulo y es de color ");
          switch(Color) {
          case 'A': printf("azul\n");
          break;
          case 'R': printf("rojo\n");
          break;
          case 'V': printf("verde\n");
          break;
		  default: printf("desconocido\n");}
                            
	 }else if((Square>=Triangle)&&(Square>=Circle)){
	   Figura='S';
	   printf("\n La figura puede ser un cuadrado y es de color ");	
	      switch(Color) {
          case 'A': printf("azul\n");
          break;
          case 'R': printf("rojo\n");
          break;
          case 'V': printf("verde\n");
          break;
		  default: printf("desconocido\n");}
                            
	 }else if((Circle>=Triangle)&&(Circle>=Square)){
	   Figura='C';
	   printf("\n La figura puede ser un circulo y es de color");
	      switch(Color) {
          case 'A': printf("azul\n");
          break;
          case 'R': printf("rojo\n");
          break;
          case 'V': printf("verde\n");
          break;
		  default: printf("desconocido\n");}	     	   	   
	 }
    	 Process_cntrl_enable_write(0);
  }else{END=0;}
 }
}

static void UART1(bool Status){
printf("Enviando datos al arduino\n");
	 if(Status){
		uart1_rxtx_write('Y');
		uart1_rxtx_write('Y');

	 }else{
		uart1_rxtx_write('N');
		uart1_rxtx_write('N');
		
	 }
	}

static void MoverMotor(short contador){
 
 if(contador==1){
	 printf("\nAcción siguiente: Mover servomotor a la derecha\n");
	 pwm_cntrl_orden_write(6);
 }else  if(contador==0){
	 printf("\nAcción siguiente: Mover servomotor al centro\n");
	 pwm_cntrl_orden_write(4);
 }else if(contador==2){
	 printf("\nAcción siguiente: Mover servomotor hacia la izquierda\n");
	 pwm_cntrl_orden_write(5);
 }else{
     printf("\nAtras no hay nada\n");
 }
}

short LeerUS(short contador){
bool ctrl=0;
short distancia=0;
bool END=0;
if(contador<3){
printf("\nPresione 1 cuando este listo para tomar la información del ultrasonido\n");
   while(!END){ 
	   ctrl=console_service(1);	
	   if(ctrl){  
	   US_cntrl_orden_write(1);
	   delay_ms(50);
	    if(US_cntrl_DONE_read()){
	       distancia=US_cntrl_d_read();
	       printf("\nLa distancia del US a la siguiente pared es de: %i", distancia);
	       printf("cm \n");
		   printf("\nPresione 1 para continuar>\n");
		   US_cntrl_orden_write(0);//reset
		   END=1;
	   }else{
		   printf("No se detecto ultrasonido, por favor conectarlo bien.");
		   delay_ms(3000);
	   }

	 }
   }
}else{distancia=50;}
 
return distancia;
}

short convertir(short contador){//direccion de entrada, dice que orientacion va a tener ahora
short Contador=0;
if(orientacion==0){
    Contador=contador;
}else if(orientacion==1){

	switch(contador) {
    case 0: Contador=1;
    break;
    case 1: Contador=3;
    break;
    case 2: Contador=0;
    break;
    case 3: Contador=2;
	}
}else if(orientacion==2){
   
    switch(contador) {
    case 0: Contador=2;
    break;
    case 1: Contador=0;
    break;
    case 2: Contador=3;
    break;
    case 3: Contador=1;
	}
}else if(orientacion==3){
    
	switch(contador) {
    case 0: Contador=3;
    break;
    case 1: Contador=2;
    break;
    case 2: Contador=1;
    break;
    case 3: Contador=0;
	} 
 }
return Contador;
}

static void MtxAssign(short distancia,short contador,short PosArray){
 short Contador=convertir(contador); //función que me convierte el contador (movimientos del motor) a direcciones espaciales segun la orientación 
 //ImageProcess();// Funcion que procesa imagen. 
  if(distancia<=15){
	  if(Contador==0){
	   Map[PosArray].paredArriba[0]='Y';
	   Map[PosArray].paredArriba[1]=Color;
	   Map[PosArray].paredArriba[2]=Figura;	  
	  }else if(Contador==1){
	   Map[PosArray].paredDer[0]='Y';
	   Map[PosArray].paredDer[1]=Color;
	   Map[PosArray].paredDer[2]=Figura;		   
	  }else if(Contador==2){
	   Map[PosArray].paredIzq[0]='Y';	  
	   Map[PosArray].paredIzq[1]=Color;
	   Map[PosArray].paredIzq[2]=Figura;		   
	  }else if(Contador==3){
	   Map[PosArray].paredAbajo[0]='Y';
	   Map[PosArray].paredAbajo[1]=Color;
	   Map[PosArray].paredAbajo[2]=Figura;		   
	  }else{
	  printf("Error");}
  }else{ 	   

	  if(Contador==0){
	  Map[PosArray].paredArriba[0]='N';	  
	  }else if(Contador==1){
	  Map[PosArray].paredDer[0]='N';
	  }else if(Contador==2){
	   Map[PosArray].paredIzq[0]='N';	
	  }else if(Contador==3){
	   Map[PosArray].paredAbajo[0]='N';	    
	  }else{
	  printf("Error");
	  }	
  }
}

static void MtxShow(short posx,short posy,short PosArray){

  printf("\nEl punto %i",posx);
  printf(",%i",posy);   
  printf(" fue caracterizado exitosamente\n");

  printf("\nEn un plano XY se determino:\n");
  printf("\nDerecha:   %c\n",Map[PosArray].paredDer[0]);
  printf("\nIzquierda: %c\n",Map[PosArray].paredIzq[0]);	  
  printf("\nArriba:    %c\n",Map[PosArray].paredArriba[0]);
  printf("\nAbajo:     %c\n",Map[PosArray].paredAbajo[0]);

  Map[PosArray].DONE=1;	  
  contTotal=contTotal+1;

}

short EvaluarInfras(){
	bool infra1 =0;
	bool infra2 =0;
	bool infra3 =0;
	bool mov=1;
	while(mov) {
		 if (infrarrojos_in_read()&1){
		  infra1=1;
		 }else { infra1=0; }
		 if (infrarrojos_in_read()&2){
		  infra2=1;
		 }else { infra2=0; }
		 if (infrarrojos_in_read()&4){
		  infra3=1;		  
		 }else { infra3=0; }


    if(infra1&infra2&infra3){ //cuando todos los infrarojos detectén negro
		mov=0;
	    UART1(mov);//---------------------->enviar mov al arduino		
		printf("\n*Detenido*(3 infra detectados)\n");
	}else if(infra2){ //cuando solo el infrarojo del centro este encendido hay movimiento
        mov=1;
		printf("\n*MOVIENDOSE*(solo 1 infra detectado)\n");
	    UART1(mov);//---------------------->enviar mov al arduino
		delay_ms(5000);
	}else{
		printf("\nEl infrarojo se salió del camino\n");
		delay_ms(5000);

	}
  }
}

///////////////////////////////////////////////FUNCIONES DE TOMAR DECISION////////////////////////////////////////////////////////

///////////////////////////////////////////////FUNCIONES DE TOMAR DECISION////////////////////////////////////////////////////////

///////////////////////////////////////////////FUNCIONES DE TOMAR DECISION////////////////////////////////////////////////////////

///////////////////////////////////////////////FUNCIONES DE TOMAR DECISION////////////////////////////////////////////////////////

short invertir(short or){
short or1=0;	
	if(or==1){or1=2;} else if(or==2){or1=1;}else if(or==3){or1=0;}else if(or==0){or1=3;}
return or1;	
}

short Priorizar(bool movArriba,bool movDer,bool movIzq,bool movAbajo,short PosArray){
//esta función recive las opciones de movimiento
short posSig=PosArray;
bool MovArriba=movArriba;
bool MovDer=movDer;
bool MovIzq=movIzq;
bool MovAbajo=movAbajo;
orientacionAnterior=orientacion;       
	    //Baja a 0 el movimiento hacia atras
 if(orientacion==0){MovAbajo=0;}
 else if(orientacion==1){MovIzq=0;}
 else if(orientacion==2){MovDer=0;}
 else if(orientacion==3){MovArriba=0;}

        //4 movimientos básicos(cuando no hay mas opción)

  if(MovArriba&!MovDer&!MovIzq&!MovAbajo){
      posSig=PosArray+4;
	  orientacion=0;
  }else if(!MovArriba&MovDer&!MovIzq&!MovAbajo){
      posSig=PosArray+1;
	  orientacion=1;
  }else if(!MovArriba&!MovDer&MovIzq&!MovAbajo){
	  posSig=PosArray-1;
	  orientacion=2;
  }else if(!MovArriba&!MovDer&!MovIzq&MovAbajo){
	  posSig=PosArray-4;                               
	  orientacion=3;
  }else if(!MovArriba&!MovDer&!MovIzq&!MovAbajo){  //Habilita el movimiento hacia atras si todas las paredes están a cerradas      
       if(orientacion==0)     {posSig=PosArray-4;  orientacion=3;}
       else if(orientacion==1){posSig=PosArray-1;  orientacion=2;}
       else if(orientacion==2){posSig=PosArray+1;; orientacion=1;}
       else if(orientacion==3){posSig=PosArray+4;  orientacion=0;}

       //cuando hay más opciones se prioriza las que no se hallan explorado
   }else if(MovArriba&MovDer&!MovIzq&!MovAbajo){
        
		if(!(Map[PosArray+4].DONE)){ //si no se ha explorado,ir.
          posSig=PosArray+4;
		  orientacion=0;
		}else if(!(Map[PosArray+1].DONE)){
          posSig=PosArray+1;
		  orientacion=1;
		}else{
			posSig=Map[PosArray].Anterior[0];
			orientacion=invertir(Map[PosArray].Anterior[1]);  //Recordar la posicion de donde vino e invertir la orientacion 
		}

   }else if(MovArriba&!MovDer&MovIzq&!MovAbajo){
        
		if(!(Map[PosArray+4].DONE)){ //si no se ha explorado,ir.
          posSig=PosArray+4;
		  orientacion=0;
		}else if(!(Map[PosArray-1].DONE)){
          posSig=PosArray-1;
		  orientacion=2;
		}else{
			posSig=Map[PosArray].Anterior[0];
			orientacion=invertir(Map[PosArray].Anterior[1]);  //Recordar la posicion de donde vino e invertir la orientacion 
		}

   }else if(MovArriba&!MovDer&!MovIzq&MovAbajo){
        
		if(!(Map[PosArray+4].DONE)){ //si no se ha explorado,ir.
          posSig=PosArray+4;
		  orientacion=0;
		}else if(!(Map[PosArray-4].DONE)){
          posSig=PosArray-4;
		  orientacion=3;
		}else{
			posSig=Map[PosArray].Anterior[0];
			orientacion=invertir(Map[PosArray].Anterior[1]);  //Recordar la posicion de donde vino e invertir la orientacion 
		}

   }else if(!MovArriba&MovDer&MovIzq&!MovAbajo){
        
		if(!(Map[PosArray+1].DONE)){ //si no se ha explorado,ir.
          posSig=PosArray+1;
		  orientacion=1;
		}else if(!(Map[PosArray-1].DONE)){
          posSig=PosArray-1;
		  orientacion=2;
		}else{
			posSig=Map[PosArray].Anterior[0];
			orientacion=invertir(Map[PosArray].Anterior[1]);  //Recordar la posicion de donde vino e invertir la orientacion 
		}

   }else if(!MovArriba&MovDer&!MovIzq&MovAbajo){
        
		if(!(Map[PosArray+1].DONE)){ //si no se ha explorado,ir.
          posSig=PosArray+1;
		  orientacion=1;
		}else if(!(Map[PosArray-4].DONE)){
          posSig=PosArray-4;
		  orientacion=3;
		}else{
			posSig=Map[PosArray].Anterior[0];
			orientacion=invertir(Map[PosArray].Anterior[1]);  //Recordar la posicion de donde vino e invertir la orientacion 
		}
 
   }else if(!MovArriba&!MovDer&MovIzq&MovAbajo){	   	   
        
		if(!(Map[PosArray-1].DONE)){ //si no se ha explorado,ir.
          posSig=PosArray-1;
		  orientacion=2;
		}else if(!(Map[PosArray-4].DONE)){
          posSig=PosArray-4;
		  orientacion=3;
		}else{
			posSig=Map[PosArray].Anterior[0];
			orientacion=invertir(Map[PosArray].Anterior[1]);  //Recordar la posicion de donde vino e invertir la orientacion 
		}

  }else{printf("Error");}


return posSig;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Evaluarpunto(short PosArray,short posx,short posy){

 bool  END=0;
 short cont=0;
 short distancia=0; 
 short ctrl=0;


printf("\nEl robot decidió moverse hacia:%i",posx); 
printf(",%i\n",posy);   

EvaluarInfras();

if (!Map[PosArray].DONE){
bhelp();
while(!END){
ctrl=console_service(1);
  if(ctrl==1){
	MoverMotor(cont);
    distancia=LeerUS(cont);
    MtxAssign(distancia,cont,PosArray);
	cont=cont+1;
   }else {
    cont=cont;
   }
 
   if(cont==4) {
	 delay_ms(50);
	 pwm_cntrl_orden_write(7);
	 MtxShow(posx,posy,PosArray);
	 END=1;
   }else{
	 cont=cont;
	 }
   }
}else{
   printf("\nEste punto ya ha sido analizado, luego no será procesado\n");
   return;
 }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
short TomarDecision(short PosArray){
   //Notamos que para moverse a la derecha hay que aumentar en 1 el valor, moverse a la izquierda restar en uno, moverse hacia arriba sumar 4 y hacia abajo restar 4.
   //(mirando hacia adelante, hay que determinar para distintas orientaciones)
   short posSiguiente=0;
   bool movArriba=0;
   bool movDer=0;
   bool movIzq=0;
   bool movAbajo;


//protocolo para explorar el laberinto y salir del laberinto
    //movimientos posibles
   if ((Map[PosArray].paredArriba[0]=='N')) {movArriba=1;}else{movArriba=0;}
   if ((Map[PosArray].paredDer[0]=='N'))    {movDer=1;}else{movDer=0;}
   if ((Map[PosArray].paredIzq[0]=='N')) {movIzq=1;}else{movIzq=0;}
   if ((Map[PosArray].paredAbajo[0]=='N')) {movAbajo=1;}else{movAbajo=0;}

   printf("\n Movimiento arriba: %i",movArriba);
   printf("\n Movimiento abajo: %i",movAbajo);
   printf("\n Movimiento izquierda: %i",movIzq);
   printf("\n Movimiento derecha: %i\n",movDer);

//decisión del movimiento siguiente
   posSiguiente=Priorizar(movArriba,movDer,movIzq,movAbajo,PosArray); 

//Asígnar un "recuerdo" de que pasó en el cuadro anterior
if(!Map[posSiguiente].DONE){
Map[posSiguiente].Anterior[0]=PosArray; 
Map[posSiguiente].Anterior[1]=orientacionAnterior; 
}
return posSiguiente;
}

void EnviarMapa(){

   printf("\n Enviando mapeo por UART %i\n");

	 for(int i=0;i<16;i++){
		uart2_rxtx_write(Map[i].paredArriba[0]);
			 }
	 delay_ms(50);
		uart2_rxtx_write(' ');
	 delay_ms(50);

	 for(int i=0;i<16;i++){
		uart2_rxtx_write(Map[i].paredAbajo[0]);
		}
	delay_ms(50);
		uart2_rxtx_write(' ');
	delay_ms(50);

	 for(int i=0;i<16;i++){
		uart2_rxtx_write(Map[i].paredDer[0]);
		}
	delay_ms(50);
		uart2_rxtx_write(' ');
	delay_ms(50);
	 for(int i=0;i<16;i++){
	    uart2_rxtx_write(Map[i].paredIzq[0]);
		}
		
   printf("\n Envio completado %i\n");


}



int main(void)
{
	irq_setmask(0);
	irq_setie(1);
	uart_init();
 

	//serial_init();
	bool init=0;
	bool end=0;
    char *str;
	char *token;
	short PosArray=0;
	short posMatrix[2]={0,0};
    short posAnterior=0;
	orientacion=0;
	contTotal=0;

	puts("\nSoC - RiscV project UNAL 2020-2-- CPU proyecto final software built "__DATE__" "__TIME__"\n");
	puts("\nPress 1 to test the modules - RiscV project -Robot Cartografo- UNAL 2020-2-- CPU proyecto final software built\n");
	puts("\nPress 2 to initialize the robot - RiscV project -Robot Cartografo- UNAL 2020-2-- CPU proyecto final software built\n");
   
	help();
	prompt();
	while(init==0) {
		init=console_service(init);
	}

//Funcionamiento del robot 
while(!end){
if(contTotal>10&PosArray==0){
	end=1;      // si vuelve a la posición 0 es porque acabo el laberinto.
}
 //Convertir posicion de array a matrix;
switch(PosArray) {
case 0: {posMatrix[0]=1; posMatrix[1]=1;}
break;
case 1: {posMatrix[0]=1; posMatrix[1]=2;}
break;
case 2: {posMatrix[0]=1; posMatrix[1]=3;}
break;
case 3: {posMatrix[0]=1; posMatrix[1]=4;}
break;
case 4: {posMatrix[0]=2; posMatrix[1]=1;}
break;
case 5: {posMatrix[0]=2; posMatrix[1]=2;}
break;
case 6: {posMatrix[0]=2; posMatrix[1]=3;}
break;
case 7: {posMatrix[0]=2; posMatrix[1]=4;}
break;
case 8: {posMatrix[0]=3; posMatrix[1]=1;}
break;
case 9:  {posMatrix[0]=3; posMatrix[1]=2;}
break;
case 10: {posMatrix[0]=3; posMatrix[1]=3;}
break;
case 11: {posMatrix[0]=3; posMatrix[1]=4;}
break;
case 12: {posMatrix[0]=4; posMatrix[1]=1;}
break;
case 13: {posMatrix[0]=4; posMatrix[1]=2;}
break;
case 14: {posMatrix[0]=4; posMatrix[1]=3;}
break;
case 15: {posMatrix[0]=4; posMatrix[1]=4;}
break;
default: {printf("Error: Movimiento fuera de la matriz"); break;} 
}
    printf("\nOrientación actual:%i\n",orientacion);
	Evaluarpunto(PosArray,posMatrix[0],posMatrix[1]);
	PosArray=TomarDecision(PosArray);
	printf("\nPuntos caracterizados:%i\n",contTotal);
}  
   
   EnviarMapa();
   printf("\nLaberinto culminado exitosamente caracterizando %i puntos\n",contTotal);

	return 0;
}

