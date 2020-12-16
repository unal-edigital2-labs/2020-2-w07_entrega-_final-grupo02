from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

# Modulo Principal
class Bloqueultrasonido(Module,AutoCSR):
    def __init__(self, ECHO,trigg):
        self.clk = ClockSignal()  #Me pide las señales 

        
         #"Atributos"  
                      #Self es el "this" de java    
        self.ECHO = ECHO
        self.trigg = trigg
        
                #REGISTROS DE LECTURA Y ESCRITURA
                                  
        self.orden= CSRStorage()
        self.DONE= CSRStatus() 
        self.d = CSRStatus(8)
     

        self.specials +=Instance("bloqueultrasonido", 
            i_clk = self.clk,
            i_orden = self.orden.storage,  #se pone el i_  o o_ para que distinga salidas o entradas
            i_ECHO = self.ECHO, # y se ponen dentro de la clase.
            o_DONE =self.DONE.status,
            o_d =self.d.status,
            o_trigg=self.trigg,

        )
        
        
       
        self.submodules.ev = EventManager()
        self.ev.ok = EventSourceProcess()
        self.ev.finalize()
 
