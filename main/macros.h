#define _ACC regs.ACC
#define _PC regs.PC

#define C_OP OP[i_op++]

#define BYTE; \
	C_OP = read_byte(regs.PC); regs.PC++;

#define WORD; \
	C_OP = read_word(regs.PC); regs.PC+=2;

#define x OP[0]
#define y OP[1]

#define Rx regs.R[x]
#define Ry regs.R[y]

#define DECODE_INSTRUCTIONS(a,b) \
	a(0x0, \
		b(0x0, WORD; BYTE; Ry = x;); 					/* MOV lit, reg */ \
		b(0x1, BYTE; BYTE; Ry = Rx;); 					/* MOV reg, reg */ \
		b(0x2, BYTE; WORD; write_word(y, Rx);); 		/* MOV reg, addr */ \
		b(0x3, WORD; BYTE; Ry = read_word(x);); 		/* MOV addr, reg */ \
		b(0x4, WORD; WORD; write_word(y, x););			/* MOV lit, addr */ \
		b(0x5, BYTE; BYTE; Ry = read_word(Rx);); 		/* MOV addr_ptr(reg), reg */ \
		b(0x6, BYTE; BYTE; write_word(Ry, Rx);); 		/* MOV reg, addr_ptr(reg) */ \
	) \
	a(0x1, \
		b(0x0, WORD; WORD; if (x != _ACC) _PC = y;);	/* JNE lit, addr */ \
		b(0x1, BYTE; WORD; if (Rx != _ACC) _PC = y;);	/* JNE reg, addr */ \
		b(0x2, WORD; WORD; if (x == _ACC) _PC = y;);	/* JEQ lit, addr */ \
		b(0x3, BYTE; WORD; if (Rx == _ACC) _PC = y;);	/* JEQ reg, addr */ \
		b(0x4, WORD; WORD; if (x < _ACC) _PC = y;);		/* JLT lit, addr */ \
		b(0x5, BYTE; WORD; if (Rx < _ACC) _PC = y;);	/* JLT reg, addr */ \
		b(0x6, WORD; WORD; if (x > _ACC) _PC = y;);		/* JGT lit, addr */ \
		b(0x7, BYTE; WORD; if (Rx > _ACC) _PC = y;);	/* JGT reg, addr */ \
		b(0x8, WORD; WORD; if (x <= _ACC) _PC = y;);	/* JLE lit, addr */ \
		b(0x9, BYTE; WORD; if (Rx <= _ACC) _PC = y;);	/* JLE reg, addr */ \
		b(0xa, WORD; WORD; if (x >= _ACC) _PC = y;);	/* JGE lit, addr */ \
		b(0xb, BYTE; WORD; if (Rx >= _ACC) _PC = y;);	/* JGE reg, addr */ \
		b(0xc, WORD; _PC = x;);							/* UCJ addr */ \
	) \
	a(0x2, \
		b(0x0, BYTE; BYTE; _ACC = Rx + Ry;);			/* ADD reg, reg */ \
		b(0x1, WORD; BYTE; _ACC = x + Ry;);				/* ADD lit, reg */ \
	) \
	a(0x3, \
		b(0x0, BYTE; BYTE; _ACC = Rx - Ry;);			/* SUB reg, reg */ \
		b(0x1, WORD; BYTE; _ACC = x - Ry;);				/* SUB lit, reg */ \
	) \
	a(0x4, \
		b(0x0, BYTE; Rx++;);							/* INC reg */ \
		b(0x1, BYTE; Rx--;);							/* DEC reg */ \
	) \
	a(0x5, \
		b(0x0, BYTE; WORD; Rx = Rx << y;);				/* LSF reg, lit */ \
		b(0x1, BYTE; BYTE; Rx = Rx << Ry;);				/* LSF reg, reg */ \
		b(0x2, BYTE; WORD; Rx = Rx >> y;);				/* RSF reg, lit */ \
		b(0x3, BYTE; BYTE; Rx = Rx >> Ry;);				/* RSF reg, reg */ \
	) \
	a(0x6, \
		b(0x0, BYTE; WORD; _ACC = Rx & Ry;);			/* AND reg, lit */ \
		b(0x1, BYTE; BYTE; _ACC = Rx & y;);				/* AND reg, reg */ \
		b(0x2, BYTE; WORD; _ACC = Rx | Ry;);			/* OR  reg, lit */ \
		b(0x3, BYTE; BYTE; _ACC = Rx | y;);				/* OR  reg, reg */ \
		b(0x4, BYTE; WORD; _ACC = Rx ^ Ry;);			/* XOR reg, lit */ \
		b(0x5, BYTE; BYTE; _ACC = Rx ^ y;);				/* AND reg, reg */ \
		b(0x6, BYTE; _ACC = ~Rx;);						/* NOT reg */ \
	)

