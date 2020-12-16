# Entrega Final - Proyecto Digital 2.

El presente proyecto tuvo como fin la creación de un robot el cual fuera capaz de recorrer un laberinto desconocido, caracterizarlo, encontrar "objetos valiosos", salir del laberinto y finalmente enviar la información encontrada via bluetooth. Para su desarrollo fue necesaria la creación de varios modulos individuales con verilog, así como la implentación de la arquitectura Risc-V,su bus de datos, mapa de memoria y unión de los modulos en el SoC, todo esto con ayuda de LiTex. Por ultimo, el software necesario para que el robot resolviera se realizó compilación cruazada con el lenguaje de programación C.


## Autores ✒️

_Menciona a todos aquellos que ayudaron a levantar el proyecto desde sus inicios_

* **Maicol Douglas Fontecha Diaz** - mdfontechad@unal.edu.co
* **Andres Cardenas Peñuela** - ancardenas@unal.edu.co
* **Valentine Muodum** - vmuodum@unal.edu.co
* **Andres Camilo Unibio Barbosa** - acunibiob@unal.edu.co

## Sistem on Chip





## Memoria



## Modulos
## Camara
## Infrarojos

## Servomotor
Para el control del servomotor se hizo uso de un driver PWM (hardware) donde se busca modificar el ciclo util de una señal de 20 ms (para este servo se busca modificar entre 0.5 y 2.5 ms el tiempo en que la señal permanece arriba) previamente generada mediante una serie de divisores de frecuencia, esta modificacion se logra mediante contadores y un parametro de suma introducido por el usuario indicando la direccion  donde el servo debe permanecer, este parametro es un numero de 0 a 180 que modifica el pulso que es mandado al servomotor logrando mantener el servo engranado en una determinada direccion hasta que el usuario decida cambiar su direccion. Este bloque se decidió hacer inicialmente en hardware para lograr independencia de la camara al hacer el mapeo, debido a que si se hace en software se debia tener un orden entre acciones (giro de servo,deteccion y toma captura de camara), por el contrario en hardaware solo se debe asignar una posicion de memoria a la direccion a la que esta mirando el robot y esto garantiza el engrane del servo a dicha direccion en todo momento, lo que elimina la necesidad de toma cuando el sensor ultrasonido no detecte nada al momento de girar, esto ultimo se traduce en optimizacion del proceso de mapeo.     
## Ultrasonido
El ultra sonido mediante un driver en hardware inicializa la medicion de la distancia  para esto es necesario generar un pulso mediante gracias al cual se envia los 8 pulsos mediante el ultrasonido y activa el contador, que haciend uso de un divisor de frecuencia y un divisor convencional es capaz contar la distancia que han recorrido los 8 pulsos iniciales que salieron del ultrasonido, y se detiene cuando estos rebotan en una suerficie y vuelve.



## Integracion


## Funcionalidad



## Videos  
En cada carpeta de modulos hay un video de cada prueba funcional individual, el video que muestra la resolucón del laberitno completo se encuentra en: 
https://www.youtube.com/watch?v=Pdu0hr4bE8M&feature=youtu.be&ab_channel=Maicolfontechadiaz
