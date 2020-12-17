# Image process

(FORMATO XRGB444 QCIF).

Para el presente modulo se partió de la idea de tomar una sola foto y analizarla directamente en el hardware, la maquina de estados para el procesamiento se muestra en una de las imagenes.


## Maquina de estados para tomar una foto:
```
INIT es un estado donde se espera que la imagen inicie, es decir, aparezca un vref,lo que indica que una nueva imagen está a punto de ser capturada.
```
BYTE1 es el estado que espera a que lleguen los href, lo que quiere decir que se comienza a capturar los datos de la fila.
```
Byte2 será donde se cuenten los pixeles de las filas
```

Ahora de Byte 2 se pasa a Byte 1 si vref y href son 0, lo que indica que se acabó lo capturado en la presente fila,luego hay que cambiar a la siguiente, quedandonos a la espera de otro href.

Finalmente, si detectamos de nuevo que hay un vref, significaría que se acabó la imagen, luego hemos tomado una foto.
![](/Hardware/Modulos/camara/Procesamiento/MaquinaEstadosFOTO.PNG)
## Procesamiento

Con base en lo anterior se planteó el procesar la imagen comparando el ancho de cada fila(siendo esta de un color de interes), luego
el hardware subido hace lo siguiente:

```
1. Espera que se detecte un color de nuestro interes en Byte2. Cuando lo cuenta,determina que color domina, y con esto crea un contador de ancho actual, sumando todos los pixeles seguidos que también sean de nuestro interes dentro de esa fila.
```

```
2. Cuando deje de detectar colores de nuestro interes, dejara de contar y guardará el ancho actual en otro registro llamado "ancho anterior". 
```

```
3. En la siguiente fila contará de nuevo el ancho actual, y al finalizarla  comparará el ancho actual con el ancho anterior
```

```
4. De esta comparación saldrán 3 resultados posibles: Un contador de anchos mayores, un contador de anchos menores y un contador de anchos iguales
```

```
5. Con esta información en software, no es muy dificil determinar si la figura fue un cuadrado, un circulo o un triangulo.
```

## Simulaciones

También se hicieron un par de simulaciones POST-SYNTESIS que parecian mostrar que el hardware funcionaria correctamente:

```
simulación cuadrado: Se puso en el test bench un solo color (Verde) y como se esperaba, el contador de anchos iguales fue 119, lo cual nos diría claramente que es un cuadrado. 
```

```
simulación triangulo: En este test bench se simulo un color que iba aumentando varios pixeles de ancho en cada fila, luego en la imagen se puede ver que detecta  77 anchos mayores, y el resto de anchos iguales (pues al final el ancho aumentó hasta salirse de la pantalla).
```
![](/Hardware/Modulos/camara/Procesamiento/SimulaciónCuadrado.jpg)
![](/Hardware/Modulos/camara/Procesamiento/SimulaciónMitadTriangulo.jpg)

## Resultados

Al unirlo con el procesador y poniendo hubieron problemas puesto que no determinaba de una manera correcta el color. No fue posible solucionar esto en el transcurso del semestre, pues no logramos determinar si era un problema de sincronización del hardware o un problema de la camara como tal.
Lo único que se pudo hacer fue conectar directamente : 11110000, y 00001111 (prueba básica.PNG) en lugar de los pines de la camara, esto resulto, efectivamente en lo esperado,pues como se ve en prueba básica 1 y 2 .PNG, el hardware es capaz de reconocer que está entrando solo verde, o azul y rojo (FORMATO XRGB444 QCIF).

## Conclusión

```
El error puede ser debido a que esperamos una imagen muy perfecta de la camara, lo cual evidentemente no se puede obtener.
```

```
También puede deberse a que haya cierto ruido externo que provoque una incorrecta captura de datos
```

```
Dado que no se tuvo el procesamiento de imagen esperado, no se incluyó en la resolución del laberinto (sin embargo el codigo software se hizo y quedó comentando en main.c)
```
