# Modulo Ultrasonido
 
 ## Funcionalidad
 Este modulo tiene como finalidad calcular la distancia entre el robot y un obstaculo cuando se le ordene. Con esto podremos identificar  
 el contorno que rodea al robot fijando una distancia de reconocimiento previa para caracterizar la deteccion, en este caso, una pared 
 que se encuentre en frente del sensor de ultrasonido. En conjunto con el módulo de servomotor y cámara el objetivo es la contruccion de un radar, 
 de tal forma que se pueda mapear un laberinto representado por una matriz, por último, esta informacion se enviará a un módulo de comunicación 
 serial (UART) para visualización. Cada posicion de esta matriz tendra informacion de un cuadrante que el robot debe caracterizar, en este caso 
 se hara uso del ultrasonido para identificar la presencia de 3 paredes, (izquierda, centro y derecha relativo a la posicion a donde mira el robot),
 ya que la de atras se supone que es de donde vino y por ende no hay pared.
 
 ## Descripcion de Hardware
 
 Para realizar la tarea de deteccion y calculo de distancia dada una orden se necesitan 2 módulos principales. El primero es un contador y el segundo 
 es un generador de pulsos PWM, cada uno funcionando con un reloj especial para interpretar cada ciclo de reloj como distancia o tiempo de encendido. 
 Estos dos módulos son controlados por una máquina de estados que transforma la variable "orden" en las combinaciones de las variables reset y ENABLE
 usadas para el funcionamiento de estos 2 módulos que son explicadas a detalle mas adelante. Para entender el funcionamiento de cada modulo adecuadamente 
 se recomienda previamente revisar el datasheet  del sensor HC-SR04.
 
 ### Modulo Contador ("contador.v")
 
 
 Este modulo tiene 2 funciones, activar la generación de un pulso PWM que hará funcionar al sensor de ultrasonido dada una orden y calcular la distancia 
 haciendo uso del sensor y su propio reloj. Este módulo cuenta con una señal de reset que deberá ser activada una vez la distancia haya sido calculada, con 
 el objetivo de limpiar las variables de estado y asi poder calcular una nueva distancia. La señal ENABLE ("orden"), se encargara de activar la  generación 
 del pulso PWM (señal pulse), e indirectamente de activar la señal ECHO, esta última permanecerá encendida hasta recibir los pulsos emitidos por el sensor 
 de la señal ENABLE dada inicialmente. El reloj de este módulo es especial ya que se diseñó de tal forma de que transforma cada ciclo de reloj en 
 centimetros haciendo uso de  la velocidad del sonido y la distancia que  recorre tanto de ida como de vuelta la señal enviada por el ultrasonido, de manera
 que, para calcular distancia basta solo con contar los ciclos de reloj desde que la señal ECHO ha sido activada hasta que se encuentre de nuevo en 0. 
 Mediante uso de variables de estado, (por ejemplo "logico"), se puede determinar cuando el sensor ha terminado de calcular la distancia y finalmente 
 entregarla al Software junto a una señal de Done y realizar la tarea de mapeo.
 
 ### Modulo Generador de pulsos ("genpulsos.v")
 
 
 Este módulo tiene como única función generar un PWM de 10 microsegundos en alto  activado por la órden del módulo contador. Este módulo cuenta con una única 
 salida llamada "trigg" dirigida a la entrada TRIGGER del sensor de ultrasonido, (señal que necesita para activarse como su nombre lo indica). El módulo funciona 
 gracias a un reloj de una periodicidad de 10 microsegundos y 2 variables de estado que controlan el PWM de salida, (indican cuando hay que subir y bajar de nivel
 el pulso para ser mas precisos). Al recibir la señal proveniente del módulo contador, ("pulse"), una de las variables de estado se activa durante un ciclo de 
 reloj  dando lugar a la activación del pulso de salida, en el siguiente ciclo un condicional se encarga de activar la otra variable de estado para forzar la 
 bajada de la señal  bajo ciertas condiciones, (esto para independizar la duración del pulso de la duración de la señal de habilitacion). Este modulo tambien cuenta
 con una señal de reset que inicializa todas la variables en 0 con el fin de poder generar otro pulso, (una vez generado un pulso la única manera de generar otro es 
 mediante la variable reset debido a la arquitectura usada).
 
 
 
 
 
 El bloque general ultrasonido, ("bloqueultrasonido.v"), tambien cuenta con otros bloques destinados al funcionamiento de la máquina de estados y a los 2 módulos 
 explicados anteriormente; sin embargo, estos módulos son simples divisores de frecuencia que funcionan manteniendo una variable en nivel alto durante n ciclos de un
 reloj principal para luego invertirla durante otros n ciclos de reloj, (la cuenta de los ciclos transcurridos se lleva en una variable auxiliar), la variable n dependerá
 de la  frecuencia del reloj principal y la del reloj deseado.El diagrama total de este modulo controladom por la maquina de estados es mostrado a continuación.
 
 ![](/Hardware/Modulos/ultrasonido/Maquina%20de%20estados%20ultrasonido.PNG)
 
 
