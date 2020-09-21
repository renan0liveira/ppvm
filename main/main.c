#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ppvm.h"

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
	init_ppvm();

	write_byte(0x0100, 0x66);
	write_byte(0x0101, 0x00);
	write_word(0x0000, 0x0f0f);

	xTaskCreate(t_run, "t_run", 2048, NULL, 0, NULL);
}
