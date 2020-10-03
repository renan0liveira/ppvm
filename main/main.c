#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>

#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "ppvm.h"
#include "terminal.h"
#include "printer.h"

static const char *TAG = "example";

static esp_vfs_spiffs_conf_t conf = {
		.base_path = "/spiffs",
		.partition_label = NULL,
		.max_files = 5,
		.format_if_mount_failed = true
};

bool init_fs()
{
	esp_err_t ret = esp_vfs_spiffs_register(&conf);
	if (ret != ESP_OK) {
		ESP_LOGE(TAG, "Failed to mount or format filesystem");
		return false;
	}
	return true;
}

bool read_code()
{
	ESP_LOGI(TAG, "Opening file");
	FILE* f = fopen("/spiffs/program.ppc", "r");
	if (f == NULL) {
		ESP_LOGE(TAG, "Failed to open code file");
		return false;
	}
	fgets((char*)mem.ram, sizeof(mem.ram), f);
	fclose(f);
	esp_vfs_spiffs_unregister(conf.partition_label);
	ESP_LOGI(TAG, "SPIFFS unmounted");

	return true;
}

void app_main(void)
{
	if (!init_fs() || !read_code()) {
		mem.PC = 0x0100;
		mem.DIR = 0x0003;

		mem.ram[0x0030] = 'n';
		mem.ram[0x0031] = 'o';
		mem.ram[0x0032] = ' ';
		mem.ram[0x0033] = 'c';
		mem.ram[0x0034] = 'o';
		mem.ram[0x0035] = 'd';
		mem.ram[0x0036] = 'e';

		mem.ram[0x0100] = 0xfa;
		mem.ram[0x0101] = 0xff;

		ESP_LOGE(TAG, "ERROR");
	}

	map_device(terminal_device);
	while(!step());
}
