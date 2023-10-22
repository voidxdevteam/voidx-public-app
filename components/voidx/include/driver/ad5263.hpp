#pragma once

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <string.h>


#define AD6263_CLOCK_SPEED_HZ	100000

class Ad5263 {
private:
	spi_device_interface_config_t devcfg_array;
	spi_device_handle_t spi_handle;
	spi_bus_config_t spi_buscfg;
	spi_transaction_t spi_stransaction[4];
	int num_devices;
	gpio_num_t gpio_cs;
	gpio_num_t gpio_miso;
	gpio_num_t gpio_mosi;
	gpio_num_t gpio_sclk;
	gpio_num_t gpio_rst;
	bool initialized;
	unsigned char * buffer;
public:
	Ad5263(int num_devices, gpio_num_t gpio_miso, gpio_num_t gpio_mosi, gpio_num_t gpio_sclk, gpio_num_t gpio_cs, gpio_num_t gpio_rst);
	void write();
	void setValue(int index, int channel, unsigned char value);
};

