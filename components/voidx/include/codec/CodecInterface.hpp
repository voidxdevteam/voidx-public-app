#pragma once
#include "../driver/i2c_bus.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2s_std.h"
#include "audioSettings.h"


#define DEFAULT_I2S_MCK_IO      (GPIO_NUM_38)
#define DEFAULT_I2S_BCK_IO      (GPIO_NUM_18)
#define DEFAULT_I2S_WS_IO       (GPIO_NUM_17)
#define DEFAULT_I2S_DO_IO       (GPIO_NUM_2)
#define DEFAULT_I2S_DI_IO       (GPIO_NUM_40)

#define DEFAULT_I2S_NUM             ((i2s_port_t)1)
#define DEFAULT_I2S_MCLK_MULTIPLE   I2S_MCLK_MULTIPLE_256

class CodecInterface {
private:
	const char * name;
protected:
	i2s_port_t i2s_port;
	i2s_std_config_t i2s_cfg;
    i2s_chan_config_t i2s_chan_cfg;
public:
	CodecInterface(const char * name);
	virtual bool initialize() = 0;
	virtual void initializeIO(){};
	virtual ~CodecInterface();
	const char * getName() { return this->name; };
	i2s_std_config_t * get_i2s_cfg() { return &this->i2s_cfg; };
	i2s_chan_config_t * get_i2s_chan_cfg() { return &this->i2s_chan_cfg; };
	i2s_port_t get_i2s_port() { return this->i2s_port; };
	virtual void setInputGain(int channel, int db) = 0;
};

namespace Codec {
	void initialize();
	CodecInterface * getActiveCodec();
	bool read_reg(uint16_t dev_addr, uint8_t reg_addr, uint8_t *data);
	bool write_reg(uint16_t dev_addr, uint8_t reg_addr, uint8_t data);
	i2s_chan_handle_t getTxChannel();
	i2s_chan_handle_t getRxChannel();
}
