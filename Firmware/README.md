# Firmware

El firmware subido contiene los test y el funcionamiento del robot en main.c. En csr.h están las funciones que permiten obtener y escribir los datos de los registros de los modulos/drivers. 

## Funcionamiento del robot 🚀

A grandes rasgos, en primer lugar se hizo un Struct de 4x4, donde cada posición debía caracterizar cada punto del mapa, luego dentro de Main tenemos 3 funciones principales:

###Evaluarpunto()
La cual como dice su nombre evalua el punto actual, en esta función se tiene en cuenta: 
   -Si se detectaron 3 infrarojos con el fin de enviarle al arduino si se debe o no detener.
   -Si está detenido, esta función se encarga de mover el servomotor para el lugar que se quiera.
   -Hacer que el ultrasonido obtenga la distancia al siguiente punto
   -con MtxAssign() se caracteriza el punto correspondiente.

Si el procesamiento de imagen hubiese funcionado adecuadamente, en esta función también iría la funcion ImageProcess(), para determinar la figura y asignarlo en la matriz.

###TomarDecision()
Esta función es netamente de software, pues lo que hace es evaluar, según lo ya caracterizado, que opciones de movimiento tiene y con base a esto elegir hacia a donde se va a mover. Dentro de esta función se guarda la posición anterior y la orientación anterior en la que venía, gracias a esto el robot tiene cierta "memoria" para saber por donde devolverse y a donde ir, ya que dado el caso de posibilidad de movimiento a 2 partes diferentes el robot siempre decidirá priorizar ir hacia lugares no explorados.

###EnviarDatos()
Con está se envian la matriz caracterizada via UART hacia un celular y de esta manera y con ayuda de un pequeño programa en c++ se logra visualizar la caracterización de una manera externa al robot.


##Envio de datos y resultados
El software fue probado y procesado, los resultados se encuentran en la carpeta "mapeoEnc++" donde apreciamos que el robot caracterizo exitosamente el laberinto propuesto.

