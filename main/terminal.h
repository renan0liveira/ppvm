#ifndef _TERMINAL_H_
#define _TERMINAL_H_

void terminal_init(void);
void terminal_write(void);

void receive_command(uint8_t size, uint8_t* params);

#endif
