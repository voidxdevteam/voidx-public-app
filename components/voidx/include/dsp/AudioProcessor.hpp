#pragma once
#include "AudioBlock.hpp"
#include "codec/CodecInterface.hpp"
#include "esp_dsp.h"
#include "esp_attr.h"

#define COMPILE_TIME_MS         10
#define CONTROL_TIME_MS         10
#define METER_MIN_VIEW_VALUE   -100.0f
#define MAX_AUDIO_BLOCKS        32

#define DEBOUNCE_TIME_CONSTANT   0.9f
#define DEBOUNCE_LEVEL           0.001f

namespace AudioProcessor
{
    void audioLoop(void * args);
    void audioInitialize(bool meters);
    void addBlock(AudioBlock * block, bool (* block_dsp)(void * ptr, float data[SAMPLING_CHANNELS][SAMPLING_FRAME]), int mode = AudioBlock::AddPushBack);
    bool channelSaturation(int channel, int io);
    float meter(int channel, int io);
    bool saturation();
    bool isInitialized();
    void displayInfo();
    void debounce(Node * ptr);
}
