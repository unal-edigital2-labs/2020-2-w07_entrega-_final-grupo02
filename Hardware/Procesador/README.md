# Procesador

Gracias al archivo buildSoCproJect.py generado mediante litex fue posible integrar todos los modulos hechos en verilog adentro del SoC risc-V. Además, litex también dio la facilidad de crear el bus de datos y el mapa de memoria para los registros de estatus y control de los perifericos. Los valores de memoria se encuentran en esta carpeta (SoC_memoryMap), aunque se mostró de una manera más grafica en la carpeta de "integración". 

Especificando un poco más lo realizado, el archivo nexys4ddr.py contiene los puertos fisicos de la fpga (de una manera analoga a los constrains de Vivado). Por otro lado, los modulos.py son la unión entre el entorno python y el hdl verilog.


