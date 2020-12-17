from migen import *
from migen.genlib.cdc import MultiReg
from litex.soc.interconnect.csr import *
from litex.soc.interconnect.csr_eventmanager import *

# Modulo Principal
class ImageProcess(Module,AutoCSR):
    def __init__(self, CAM_px_data,CAM_href,CAM_vsync,CAM_pclk,CAM_xclk,CAM_pwdn):
        self.clk = ClockSignal()  #Me pide las señales 

        
         #"Atributos"  
                      #Self es el "this" de java    
        self.CAM_px_data = CAM_px_data
        self.CAM_href = CAM_href
        self.CAM_vsync = CAM_vsync
        self.CAM_pclk = CAM_pclk
        self.CAM_xclk = CAM_xclk
        self.CAM_pwdn = CAM_pwdn 
                        
                #REGISTROS DE LECTURA Y ESCRITURA
                                  
        self.enable = CSRStorage()
        self.CAM_reset = CSRStorage()
        self.END = CSRStatus() 
        self.AnchoMayor = CSRStatus(12)
        self.AnchoMenor = CSRStatus(12)
        self.AnchoIgual = CSRStatus(12)
        self.redCounter = CSRStatus(20) 
        self.greenCounter = CSRStatus(20)
        self.blueCounter = CSRStatus(20)
        self.nothingCounter = CSRStatus(20)

     

        self.specials +=Instance("imageProcess", 
            i_clk = self.clk,
            i_CAM_px_data = self.CAM_px_data,
            i_CAM_href = self.CAM_href,
            i_CAM_vsync = self.CAM_vsync,
            i_CAM_pclk = self.CAM_pclk,
            o_CAM_xclk = self.CAM_xclk,
            o_CAM_pwdn = self.CAM_pwdn,  #se pone el i_  o o_ para que distinga salidas o entradas
            i_enable = self.enable.storage,
            i_CAM_reset = self.CAM_reset.storage,
            o_END =self.END.status,
            o_AnchoMayor =self.AnchoMayor.status,
            o_AnchoMenor =self.AnchoMenor.status,
            o_AnchoIgual =self.AnchoIgual.status,
            o_redCounter =self.redCounter.status,
            o_greenCounter =self.greenCounter.status,
            o_blueCounter =self.blueCounter.status,
            o_nothingCounter =self.nothingCounter.status,
            

        )
        
        
       
        self.submodules.ev = EventManager()
        self.ev.ok = EventSourceProcess()
        self.ev.finalize()
 
