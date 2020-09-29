#include "ssd1306.h"
#include "ssd1306_draw.h"
#include "ssd1306_font.h"
#include "ssd1306_default_if.h"

#include <string.h>
#include <stdbool.h>
#include "terminal.h"

static const int I2CDisplayAddress = 0x3C;
static const int I2CDisplayWidth = 128;
static const int I2CDisplayHeight = 64;
static const int I2CResetPin = -1;
struct SSD1306_Device I2CDisplay;

static u8* terminal_memory;

static char lines[5][19] = {"","","","",""};
static u8 curr_line = 0;

static void exec(u16 mask){
	if(curr_line == 4){
		SSD1306_Clear( &I2CDisplay, SSD_COLOR_BLACK );
		for (u8 i = 1; i < 5; i++){
			memcpy(lines[i-1], lines[i], 19);
		}
	} else { curr_line++; }

	memcpy(lines[curr_line], terminal_memory, 20);

	SSD1306_FontDrawString(&I2CDisplay, 0, 0, lines[0], SSD_COLOR_WHITE);
	SSD1306_FontDrawString(&I2CDisplay, 0, 13, lines[1], SSD_COLOR_WHITE);
	SSD1306_FontDrawString(&I2CDisplay, 0, 26, lines[2], SSD_COLOR_WHITE);
	SSD1306_FontDrawString(&I2CDisplay, 0, 39, lines[3], SSD_COLOR_WHITE);
	SSD1306_FontDrawString(&I2CDisplay, 0, 52, lines[4], SSD_COLOR_WHITE);
	SSD1306_Update(&I2CDisplay);
}

static bool DefaultBusInit( void ) {
	assert(SSD1306_I2CMasterInitDefault() == true);
	assert(SSD1306_I2CMasterAttachDisplayDefault(&I2CDisplay, I2CDisplayWidth, I2CDisplayHeight, I2CDisplayAddress, I2CResetPin) == true);

    return true;
}

static void map_terminal(u8* memory){
	if (DefaultBusInit() == true) {
		SSD1306_SetFont(&I2CDisplay, &Font_droid_sans_mono_7x13);
		SSD1306_Clear( &I2CDisplay, SSD_COLOR_BLACK );
		terminal_memory = memory;
		*(terminal_memory + 20) = '\0';
	}
}

const device_t terminal_device = {
		.size = 20,
		.mask_size = 2,
		.map_fn = map_terminal,
		.exec_fn = exec
};
