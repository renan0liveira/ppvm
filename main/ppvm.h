#ifndef _PPVM_H_
#define _PPVM_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "device.h"
#include "macros.h"

typedef uint8_t u8;
typedef uint16_t u16;

typedef struct dmt_{
	u8 mask_size;
	void (*exec_fn)(u16 mask);
	struct dmt_* next;
} device_map_t;

// PC deve começar com 0x0100
typedef union {
	struct
	{
		u16 GR[16];
		u16 ACC;
		u16 DIR;
		u16 PC;
		u16 OP[2];
	};
	u16 R[18];
	u8 ram[65536];
} Memory;

Memory mem;
void map_device(device_t);
bool step(void);

#endif
