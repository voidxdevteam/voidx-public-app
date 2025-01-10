#pragma once
#include "CodecInterface.hpp"
#include "driver/i2c.h"
#include "driver/i2s.h"
#include "esp_types.h"
#include "esp_err.h"
#include "driver/gpio.h"

class Pcm1865: public CodecInterface {
private:
	static constexpr const char * name = "PCM1865";
    uint16_t dev_addr;
	int gains[2];
public:
	Pcm1865(uint16_t address);
	bool initialize();
	void initializeIO();
	void setInputGain(int channel, int db);
	virtual ~Pcm1865();
};
