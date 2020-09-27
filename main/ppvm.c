#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "ppvm.h"
#include "macros.h"

static Memory mem;
static u16 reserved_memory_bound = 0x0030;

static device_map_t* device_map = NULL;
static u8 total_mask_size = 0;

void init_ppvm(void)
{
	mem.PC = 0x0100;
}
void map_device(device_t device)
{
	device.map_fn(mem.ram + reserved_memory_bound);
	reserved_memory_bound += device.size;

	device_map_t* new_device = (device_map_t *)malloc(sizeof(device_map_t));

	new_device->mask_size =  device.mask_size;
	new_device->exec_fn = device.exec_fn;
	new_device->next = NULL;

	if (device_map == NULL) {
		device_map = new_device;
	} else {
		device_map_t* last_device = device_map;
		while(last_device->next != NULL){
			last_device = last_device->next;
		}
		last_device->next = new_device;
	}

	total_mask_size += device.mask_size;
}

u8 read_byte(u16 addr){
	return mem.ram[addr];
}
void write_byte(u16 addr, u8 byte)
{
	mem.ram[addr] = byte;
}
u16 read_word(u16 addr)
{
	return (mem.ram[addr] * 0x100) + mem.ram[addr + 1];
}
void write_word(u16 addr, u16 word)
{
	mem.ram[addr] = word >> 8;
	mem.ram[addr + 1] = word;
}
void exec_instruction(u8 opcode)
{
	u8 i_op = 0;
	#define a(ms4bytes, ops1) if (((opcode >> 4)|0) == ms4bytes) { ops1 } else
	#define b(ls4bytes, ops2) if ((opcode & 0x0f) == ls4bytes) { ops2 return;} else
	DECODE_INSTRUCTIONS(a,b) {}
	#undef b
	#undef a
}
void exec_devices()
{
	device_map_t* curr_device = device_map;
	u16 mask;
	while (mem.DIR > 0 && curr_device != NULL) {
		mask = mem.DIR & ~(0xFFFF << curr_device->mask_size);
		if (mask) { curr_device->exec_fn(mask); }

		mem.DIR >>= curr_device->mask_size;
		curr_device = curr_device->next;
	}
}

void step()
{
	exec_instruction(read_byte(mem.PC++));
	exec_devices();
//	printf("%#06x\n", mem.DIR);
}
