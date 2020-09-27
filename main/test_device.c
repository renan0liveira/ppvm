#include "test_device.h"
#include <stdio.h>

static u8* test_memory;

static void exec(u16 mask) {
	printf("hello i'm test\n");
}

static void map_test(u8* memory){
	test_memory = memory;
}

const device_t test_device = {
		.size = 10,
		.mask_size = 1,
		.map_fn = map_test,
		.exec_fn = exec
};
