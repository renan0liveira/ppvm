#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;

typedef struct {
	u16 size;
	u8 mask_size;
	void (*map_fn)(u8* memory);
	void (*exec_fn)(u16 mask);
} device_t;

#endif
