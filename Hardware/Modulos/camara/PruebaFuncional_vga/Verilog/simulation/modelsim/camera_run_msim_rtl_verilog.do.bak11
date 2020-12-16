transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources/PLL {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources/PLL/clk25_24_altera_cyclone_iv.v}
vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources/VGA_driver.v}
vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources/test_cam.v}
vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources/cam_read.v}
vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/sources/buffer_ram_dp.v}
vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/db {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/db/clk25_24_altera_cyclone_iv_altpll.v}

vlog -vlog01compat -work work +incdir+D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/simulation {D:/UNAL/semester7/Digital/Digital_ii_proyecto/camara/simulation/test_cam_TB.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  test_cam_TB

add wave *
view structure
view signals
run 1000 ns
