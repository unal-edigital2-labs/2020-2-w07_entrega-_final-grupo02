# Servomotor SG90
Para el control del servomotor se hizo uso de un driver PWM (hardware) donde se busca modificar el ciclo util de una señal de 20 ms (para este servo se busca modificar entre 0.5 y 2.5 ms el tiempo en que la señal permanece arriba) previamente generada mediante una serie de divisores de frecuencia, esta modificacion se logra mediante contadores y un parametro de suma introducido por el usuario indicando la direccion  donde el servo debe permanecer, este parametro es un numero de 0 a 180 que modifica el pulso que es mandado al servomotor logrando mantener el servo engranado en una determinada direccion hasta que el usuario decida cambiar su direccion. Este bloque se decidió hacer inicialmente en hardware para lograr independencia de la camara al hacer el mapeo, debido a que si se hace en software se debia tener un orden entre acciones (giro de servo,deteccion y toma captura de camara), por el contrario en hardaware solo se debe asignar una posicion de memoria a la direccion a la que esta mirando el robot y esto garantiza el engrane del servo a dicha direccion en todo momento, lo que elimina la necesidad de toma cuando el sensor ultrasonido no detecte nada al momento de girar, esto ultimo se traduce en optimizacion del proceso de mapeo.
 ##Descripcion de HardWare
Para realizar la funcion de modificar el ancho del pulso PWM se cuenta con una divisor de frecuencia para obtener una señal de frecuencia de 20ms a esta señal se le imprimira un pulso del ancho segun lo desee el usuario mediante el input ORDEN con el cual este input se divide en dos partes el bit mas significativo el cual funciona como reset si es 0 y como enable si es 1, gracias a este enable el generador de los pulsos PWM comienza a funcionar para despues, gracias a los otros dos bits del input orden y haciendo uso de una maquina de estados simple, modificar el ancho de la señal PWM siendo 00=1ms 01=2ms 10=0.5ms 
Para este fin se cuenta con los siguientes modulos: 

##Divisor de Frecuencia (DivFreqPWM.v)
 El cual haciendo uso del relog de 100MHz devuelte un reloj de 20kHz.

##Maquina de estados PWM (MaqinaEstadosPWM.v)
Recibe una orden la cual activa o desactiva el generador pwm, lo reinicia y ademas selecciona el ancho del pulso el cual se ve reflejado en el angulo del servo motor.

##PWM (PWM.v)
Recibe los el dato grados del modulo anterior le cual establece el ancho de pulso para poder lograr -90° 0° y 90° en el servo y brindando la señal PWM final.
 
