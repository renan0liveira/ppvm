#ifndef _PPVM_H_
#define _PPVM_H_

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;

typedef union {
	struct
	{
		u16 GR[16];
		u16 ACC;
		u16 PC;
		u16 OP[2];
	};
	u16 R[17];
	u8 ram[65536];
} Memory;

void init_ppvm(void);

u8 read_byte(u16 addr);
void write_byte(u16 addr, u8 byte);
u16 read_word(u16 addr);
void write_word(u16 addr, u16 word);

void exec_instruction(u8 opcode);
void step(void);

#endif
