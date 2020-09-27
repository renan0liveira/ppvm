#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ppvm.h"
#include "printer.h"
#include "test_device.h"

void t_run(void* param)
{
	bool run = true;
	while(1){
		if(run){
			step();
			run = false;
		}
	}
}

void app_main(void)
{
	write_byte(0x0030, 0x5A);
	write_byte(0x0031, 0x69);
	write_byte(0x0032, 0x6B);
	write_byte(0x0033, 0x61);
	write_byte(0x0034, 0x00);

	write_byte(0x0100, 0x00);
	write_word(0x0101, 0x0002);
	write_byte(0x0103, 0x11);

	map_device(printer_device);
	map_device(test_device);
	init_ppvm();
	xTaskCreate(t_run, "t_run", 2048, NULL, 0, NULL);
}
