# Entrega Final - Proyecto Digital 2.

El presente proyecto tuvo como fin la creación de un robot el cual fuera capaz de recorrer un laberinto desconocido, caracterizarlo, encontrar "objetos valiosos", salir del laberinto y finalmente enviar la información encontrada via bluetooth. Para su desarrollo fue necesaria la creación de varios modulos individuales con verilog, así como la implentación de la arquitectura Risc-V,su bus de datos, mapa de memoria y unión de los modulos en el SoC, todo esto con ayuda de LiTex. Por ultimo, el software necesario para que el robot resolviera se realizó compilación cruazada con el lenguaje de programación C.


## Autores ✒️

* **Maicol Douglas Fontecha Diaz** - mdfontechad@unal.edu.co
* **Andres Cardenas Peñuela** - ancardenas@unal.edu.co
* **Valentine Muodum** - vmuodum@unal.edu.co
* **Andres Camilo Unibio Barbosa** - acunibiob@unal.edu.co

## Diseño y funcionalidad.
Haciendo una pequeña descripción del robot, este se diseño para resolver un laberinto de 4x4 el cual le fuese desconocido. Así pues partimos de diseñar modulos que sirvan para identificar los elementos externos: Ultrasonido,Camara y servomotor para direccionar estos dos ultimos. También tenemos modulos de gpio para obtener la información de una especie de seguidor de linea para moverse por el mapa, adicionalmente tenemos dos puertos UART para la comunicación con un arduino (el cual teoricamente moveria el motor) y otra UART para comunicarse por bluetooth con dispositivos externos.

Se intentó hacer un modulo de procesamiento de imagen para el reconocimiento de figuras a lo largo del laberinto, sin embargo por distintos (quizá sutiles errores) no funcionó, luego aunque se hizo su software, no se incluyó en el recorrido del laberinto, todo esto se explica de una mejor manera en cada submodulo de este repositorio.

Con todos los modulos de hardware se utilizó un procesador para unirlos y ponerlos a trabajar juntos. Con ello se realizó el software correspondiente y se consiguió recorrer unos cuantos laberintos (dandole los estimulos de una manera manual).
![](/Captura%20de%20pantalla%20de%202020-12-16%2019-34-48.png)
## Videos  
En cada carpeta de modulos hay un video de cada prueba funcional individual, el video que muestra la resolucón del laberitno completo se encuentra en: 
https://www.youtube.com/watch?v=Pdu0hr4bE8M&feature=youtu.be&ab_channel=Maicolfontecha
