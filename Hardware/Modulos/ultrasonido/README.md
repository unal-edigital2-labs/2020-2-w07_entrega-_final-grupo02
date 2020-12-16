# Modulo Ultrasonido
 
 ## Funcionalidad
 Este modulo tiene como finalidad calcular la distancia entre el robot y un obstaculo cuando se le ordene. Con esto podremos identificar  
 el contorno que rodea al robot fijando una distancia de reconocimiento previa para caracterizar la deteccion de en este caso, una pared 
 que se encuentre en frente del sensor de ultrasonido. En conjunto con el modulo de servomotor y camara se pretende la contruccion de un radar, 
 de tal forma que se pueda mapear un laberinto representado por una matriz, por ultimo esta informacion se enviara a un modulo de comunicacion 
 serial (UART) para visualizacion. Cada posicion de esta matriz tendra informacion de un cuadrante que el robot debe caracterizar, en este caso 
 se hara uso del ultrasonido para identificar la presencia de 3 paredes (izquierda, centro y derecha relativo a la posicion a donde mira el robot)
 ya que la de atras se supone que es de donde vino y por ende no hay pared.
 
 ## Descripcion de Hardware
 
 Para realizar la tarea de deteccion y calculo de distancia dada una orden se necesitan 2 modulos principales. El primero es un contador y el segundo 
 es un generador de pulsos PWM, cada uno funcionando con un reloj especial para interpretar cada ciclo de reloj como distancia o tiempo de encendido.
 Para entender el funcionamiento de cada modulo adecuadamente se recomienda previamente revisar el datasheet del sensor HC-SR04.
 
 ### Modulo Contador (contador.v)
 
 Este modulo tiene 2 funciones, activar la generacion de un pulso PWM que hara funcionar al sensor de ultrasonido dada una orden y calcular la distancia 
 haciendo uso del sensor y su propio reloj. Este modulo cuanta con una señal de reset que deberá ser activada una vez la distancia haya sido calculada con 
 el objetivo de limpiar las variables de estado y asi poder calcular una nueva distancia. La señal ENABLE ("orden"), se encargara de activar la  generación del pulso
 PWM (señal pulse), e indirectamente de activar la señal ECHO, esta ultima permanecera encendida hasta recibir los pulsos emitidos por el sensor cuando se dio la señal 
 ENABLE inicialmente. El reloj de este modulo es especial ya que se diseño de tal forma de que transforma cada ciclo de reloj en centimetros haciendo uso de 
 la velocidad del sonido y la distancia que  recorre tanto de ida como de vuelta la señal enviada por el ultrasonido, de manera que para calcular distancia
 basta solo con contar los ciclos de reloj desde que la señal ECHO ha sido activada hasta que se encuentre de nuevo en 0. Mediante uso de variables de estado 
 (por ejemplo "logico") se puede determinar cuando el sensor ha terminado de calcular la distancia para finalmente entregarla al Software junto a una señal de 
 done para poder realizar la tarea de mapeo.
 
 ### Modulo Generador de pulsos (genpulsos.v)
 
 
 
 
