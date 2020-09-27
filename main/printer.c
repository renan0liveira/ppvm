#include "printer.h"
#include <stdio.h>

static u8* printer_memory;

static void exec(u16 mask) {
	printf("%s\n", printer_memory);
}

static void map_printer(u8* memory){
	printer_memory = memory;
}

const device_t printer_device = {
		.size = 20,
		.mask_size = 1,
		.map_fn = map_printer,
		.exec_fn = exec
};
