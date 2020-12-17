from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

# Modulo Principal
class BloquePWM(Module,AutoCSR):
    def __init__(self, pwm):
        self.clk = ClockSignal()  #Me pide las señales 
        
         #"Atributos"  
                      #Self es el "this" de java    
        self.pwm = pwm
        
                #REGISTROS DE LECTURA Y ESCRITURA
                                  
        self.orden = CSRStorage(3) #ALMACENAR, GUARDAR 3BITS, LECTURA Y ESCRITURA  /(AUNQUE SOLO SE NECESITE ESCRITURA)

        self.specials +=Instance("bloquePWM", 
            i_clk = self.clk,
            i_orden = self.orden.storage,  #se pone el i_  o o_ para que distinga salidas o entradas
            o_pwm = self.pwm, # y se ponen dentro de la clase.
            
        )
        
        
       
        self.submodules.ev = EventManager()
        self.ev.ok = EventSourceProcess()
        self.ev.finalize()
 
