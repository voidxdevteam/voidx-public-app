#pragma once
#include "AudioBlock.hpp"
#include "codec/CodecInterface.hpp"
#include "esp_dsp.h"
#include "esp_attr.h"

#define COMPILE_TIME_MS 10
#define METER_MIN_VALUE -110.0f

namespace AudioProcessor
{
    void IRAM_ATTR audioLoop(void * args);
    void audioInitialize(Node * parent);
    void addBlock(AudioBlock * block, int mode = AudioBlock::AddPushBack);
    bool channelSaturation(int channel, int io);
    float meter(int channel, int io);
    bool saturation();
    bool isInitialized();
}
