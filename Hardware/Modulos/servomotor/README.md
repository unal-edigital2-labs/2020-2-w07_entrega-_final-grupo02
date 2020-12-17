# Servomotor SG90
Para el control del servomotor se hizo uso de un driver PWM (hardware) donde se busca modificar el ciclo util de una señal de 20 ms (para este servo se busca modificar entre 0.5 y 2.5 ms el tiempo en que la señal permanece arriba) previamente generada mediante una serie de divisores de frecuencia, esta modificacion se logra mediante contadores y un parametro de suma introducido por el usuario indicando la direccion  donde el servo debe permanecer, este parametro es un numero de 0 a 180 que modifica el pulso que es mandado al servomotor logrando mantener el servo engranado en una determinada direccion hasta que el usuario decida cambiar su direccion. Este bloque se decidió hacer inicialmente en hardware para lograr independencia de la camara al hacer el mapeo, debido a que si se hace en software se debia tener un orden entre acciones (giro de servo,deteccion y toma captura de camara), por el contrario en hardaware solo se debe asignar una posicion de memoria a la direccion a la que esta mirando el robot y esto garantiza el engrane del servo a dicha direccion en todo momento, lo que elimina la necesidad de toma cuando el sensor ultrasonido no detecte nada al momento de girar, esto ultimo se traduce en optimizacion del proceso de mapeo.

  ## Descripcion de HardWare
 Para realizar la funcion de modificar el ancho del pulso PWM se cuenta con una divisor de frecuencia para obtener una señal de frecuencia de 20ms a esta señal se le   imprimira un pulso del ancho segun lo desee el usuario mediante el input ORDEN con el cual este input se divide en dos partes el bit mas significativo el cual      funciona como reset si es 0 y como enable si es 1, gracias a este enable el generador de los pulsos PWM comienza a funcionar para despues, gracias a los otros dos bits del input orden y haciendo uso de una maquina de estados simple, modificar el ancho de la señal PWM siendo 00=1ms 01=2ms 10=0.5ms 
Para este fin se cuenta con los siguientes modulos: 

  ## Divisor de Frecuencia (DivFreqPWM.v)
 
 El cual haciendo uso del relog de 100MHz devuelve un reloj de 20kHz.
## Maquina de estados PWM (MaqinaEstadosPWM.v)

 Recibe una orden la cual activa o desactiva el generador pwm, lo reinicia y ademas selecciona el ancho del pulso el cual se ve reflejado en el angulo del servo   motor, en cuanto a esto este modulo recibe el input orden de 3 bits la cual se pasa por 2 algoritmos del tipo case, el primero comprueba el bit mas significativo para activar el generador PWM o hacer reset si fuese necesario, en el segundo se segun su respectivo valor de 0 a 2  se devuelven 2 bits tambien de 0 a 2 los cuales controlan el ancho la señal PWM
## PWM (PWM.v)
 
 Recibe los el input grado de 2 bits con el cual mediante mediante un Case asignaria un valor la variable ancho de entre 10 a 50 que junto con el reloj de 20kHz y un contador integrado a este mismo modulo se generiaria una señal de 20kHz dutty cycle de duracion etre 0.5ms a 2ms lo cual le permitira al servo motor girar entre -90 0 90 grados y que permitira al ultra sonido y a la camara enfocar todas las paredes adyacentes.
![](/Hardware/Modulos/servomotor/Pwm.png) 
