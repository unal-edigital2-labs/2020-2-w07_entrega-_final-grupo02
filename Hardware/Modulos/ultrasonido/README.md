# Modulo Ultrasonido
 
 ## Funcionalidad
 Este modulo tiene como finalidad calcular la distancia entre el robot y un obstaculo cuando se le ordene. Con esto podremos identificar  
 el contorno que rodea al robot fijando una distancia de reconocimiento previa para caracterizar la deteccion de en este caso, una pared 
 que se encuentre en frente del sensor de ultrasonido. En conjunto con el modulo de servomotor y camara se pretende la contruccion de un radar, 
 de tal forma que se pueda mapear un laberinto representado por una matriz, por ultimo esta informacion se enviara a un modulo de comunicacion 
 serial (UART) para visualizacion.cada posicion de esta matriz tendra informacion de un cuadrante que el robot debe caracetrizar, en este caso 
 se hara uso del ultrasonido para identificar la presencia de 3 paredes (izquierda, centro y derecha relativo a la posicion a donde mira el robot)
 ya que la de atras se supone que es de donde vino y por ende no hay pared.
 
 ## Descripcion de Hardware
 
 Para realizar la tarea de deteccion y calculo de distancia dada una orden se necesitan 2 modulos principales. El primero es un contador y el segundo 
 es un generador de pulsos PWM, cada uno funcionando con un reloj especial para interpretar cada ciclo de reloj como distancia o tiempo de encendido.
 
 ### Modulo Contador 
 
 Este modulo tiene 2 funciones, activar la generacion de un pulso PWM que hara funcionar al sensor de ultrasonido dada una orden y calcular la distancia 
 despues de mandado el pulso mediante la señal ECHO dada por el sensor
 
