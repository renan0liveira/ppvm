#include "ssd1306.h"
#include "ssd1306_draw.h"
#include "ssd1306_font.h"
#include "ssd1306_default_if.h"

#include <stdio.h>

#include "terminal.h

static const int I2CDisplayAddress = 0x3C;
static const int I2CDisplayWidth = 128;
static const int I2CDisplayHeight = 64;
static const int I2CResetPin = -1;

struct SSD1306_Device I2CDisplay;
char* lines[5] = {"","","","",""};

void terminal_init(void)
{}

void terminal_write(void)
{}

void receive_command(uint8_t size, uint8_t* params)
{
	printf("size: %d\n", size);
	printf("fisrt param: %d\n", params[0]);
}
