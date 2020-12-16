from migen import *
from migen.genlib.io import CRG
from migen.genlib.cdc import MultiReg

import nexys4ddr as tarjeta
#import c4e6e10 as tarjeta

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.interconnect.csr import *

from litex.soc.cores import gpio
from litex.soc.cores import uart

from module import rgbled
from module import sevensegment
from module import vgacontroller
from module import bloquePWM
from module import bloqueultrasonido
from module import imageProcess






# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
	def __init__(self):
		platform = tarjeta.Platform()
		
		## add source verilog

		#PWM
		platform.add_source("module/verilog/bloquePWM.v")
		platform.add_source("module/verilog/MaquinaEstadosPWM.v")
		platform.add_source("module/verilog/PWM.v")
		platform.add_source("module/verilog/DivFreqPWM.v")
        #ULTRASONIDO
		platform.add_source("module/verilog/contador.v")
		platform.add_source("module/verilog/divisor.v")
		platform.add_source("module/verilog/divisorfrec.v")
		platform.add_source("module/verilog/divisorfrecd.v")
		platform.add_source("module/verilog/divisorfrecgen.v")
		platform.add_source("module/verilog/divisorfrecme.v")
		platform.add_source("module/verilog/genpulsos.v")
		platform.add_source("module/verilog/maquinadeestados.v")
		platform.add_source("module/verilog/meultrasonido.v")
		platform.add_source("module/verilog/ultrasonido.v")
		platform.add_source("module/verilog/bloqueultrasonido.v")

        #IMAGE PROCESS
		platform.add_source("module/verilog/imageProcess.v")
		platform.add_source("module/verilog/clk24_25_nexys4.v")
		platform.add_source("module/verilog/clk24_25_nexys4_clk_wiz.v")	

		# SoC with CPU
		SoCCore.__init__(self, platform,
 			cpu_type="picorv32",
#			cpu_type="vexriscv",
			clk_freq=100e6,
			integrated_rom_size=0x8000,
			integrated_main_ram_size=16*1024)




		# Clock Reset Generation
		self.submodules.crg = CRG(platform.request("clk"), ~platform.request("cpu_reset"))  #Función que me define un modulo el cual solicita y se activa por los pines

		# Leds
		SoCCore.add_csr(self,"leds")
		user_leds = Cat(*[platform.request("led", i) for i in range(10)])
		self.submodules.leds = gpio.GPIOOut(user_leds)
		
		# Switchs
		SoCCore.add_csr(self,"switchs")
		user_switchs = Cat(*[platform.request("sw", i) for i in range(8)])
		self.submodules.switchs = gpio.GPIOIn(user_switchs)
		
		# Buttons
		SoCCore.add_csr(self,"buttons")
		user_buttons = Cat(*[platform.request("btn%c" %c) for c in ['c','r','l']])
		self.submodules.buttons = gpio.GPIOIn(user_buttons)
		
		# 7segments Display
		SoCCore.add_csr(self,"display")
		display_segments = Cat(*[platform.request("display_segment", i) for i in range(8)])
		display_digits = Cat(*[platform.request("display_digit", i) for i in range(8)])
		self.submodules.display = sevensegment.SevenSegment(display_segments,display_digits)

		# RGB leds
		SoCCore.add_csr(self,"ledRGB_1")
		self.submodules.ledRGB_1 = rgbled.RGBLed(platform.request("ledRGB",1))
		
		SoCCore.add_csr(self,"ledRGB_2")
		self.submodules.ledRGB_2 = rgbled.RGBLed(platform.request("ledRGB",2))
		
				
		# VGA
		SoCCore.add_csr(self,"vga_cntrl")
		vga_red = Cat(*[platform.request("vga_red", i) for i in range(4)])
		vga_green = Cat(*[platform.request("vga_green", i) for i in range(4)])
		vga_blue = Cat(*[platform.request("vga_blue", i) for i in range(4)])
		self.submodules.vga_cntrl = vgacontroller.VGAcontroller(platform.request("hsync"),platform.request("vsync"), vga_red, vga_green, vga_blue)
		
		# Buttons
		SoCCore.add_csr(self,"ctrlButton")
		user_buttons1 = Cat(*[platform.request("btn%c" %c) for c in ['I','H']])
		self.submodules.ctrlButton = gpio.GPIOIn(user_buttons1)


		#UART1 (arduino)

		from litex.soc.cores import uart
		self.submodules.uart1_phy = uart.UARTPHY(
			pads     = platform.request("uart1"),
			clk_freq = self.sys_clk_freq,
			baudrate = 115200)
		self.submodules.uart1 = ResetInserter()(uart.UART(self.uart1_phy,
			tx_fifo_depth = 16,
			rx_fifo_depth = 16))
		self.csr.add("uart1_phy", use_loc_if_exists=True)
		self.csr.add("uart1", use_loc_if_exists=True)
		if hasattr(self.cpu, "interrupt"):
			self.irq.add("uart1", use_loc_if_exists=True)
		else:
			self.add_constant("UART_POLLING")

		#UART2 (bluetooth)

		from litex.soc.cores import uart
		self.submodules.uart2_phy = uart.UARTPHY(
			pads     = platform.request("uart2"),
			clk_freq = self.sys_clk_freq,
			baudrate = 9600)
		self.submodules.uart2 = ResetInserter()(uart.UART(self.uart2_phy,
			tx_fifo_depth = 16,
			rx_fifo_depth = 16))
		self.csr.add("uart2_phy", use_loc_if_exists=True)
		self.csr.add("uart2", use_loc_if_exists=True)
		if hasattr(self.cpu, "interrupt"):
			self.irq.add("uart2", use_loc_if_exists=True)
		else:
			self.add_constant("UART_POLLING")
       #Infrarojos
		SoCCore.add_csr(self,"infrarrojos")
		Infras = Cat(*[platform.request("infrarrojos", i) for i in range(3)])
		self.submodules.infrarrojos = gpio.GPIOIn(Infras)

       #pwm
		SoCCore.add_csr(self,"pwm_cntrl") 
#	//	SoCCore.add_interrupt(self,"pwm_cntrl")
		self.submodules.pwm_cntrl = bloquePWM.BloquePWM(platform.request("pwm"))
		
       #ultrasonido
		SoCCore.add_csr(self,"US_cntrl") 
 #    	SoCCore.add_interrupt(self,"US_cntrl")
		self.submodules.US_cntrl = bloqueultrasonido.Bloqueultrasonido(platform.request("ECHO"),platform.request("trigg"))

       #imageProcess
		SoCCore.add_csr(self,"Process_cntrl") 
#		SoCCore.add_interrupt(self,"Process_cntrl")
		CAM_px_data = Cat(*[platform.request("CAM_px_data", i) for i in range(8)])
		self.submodules.Process_cntrl = imageProcess.ImageProcess(CAM_px_data,platform.request("CAM_href"),platform.request("CAM_vsync"),platform.request("CAM_pclk"),platform.request("CAM_xclk"),platform.request("CAM_pwdn"))


# Build --------------------------------------------------------------------------------------------



if __name__ == "__main__":
	builder = Builder(BaseSoC(),csr_csv="Soc_MemoryMap.csv")  #BUSCA EL MAPA DE MEMORIA
	builder.build()


