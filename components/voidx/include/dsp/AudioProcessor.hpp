#pragma once
#include "AudioBlock.hpp"
#include "codec/CodecInterface.hpp"
#include "esp_dsp.h"

#define COMPILE_TIME_MS 10
#define METER_MIN_VALUE -110.0f

namespace AudioProcessor
{
    void audioLoop(void * args);
    void audioInitialize(Node * parent);
    void addBlock(AudioBlock * block);
    float meter(int channel, int io);
    bool isInitialized();
}
