#include <stdint.h>
#include <stdio.h>

#include "ppvm.h"
#include "macros.h"

static Memory mem;

void init_ppvm(void)
{
	mem.PC = 0x0100;
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

void step()
{
	exec_instruction(read_byte(mem.PC++));

	printf("%#06x\n", mem.ACC);
}

// usar o terminal diretamente dentro da vm
