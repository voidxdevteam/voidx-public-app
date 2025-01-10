#pragma once
#include "tusb.h"
#include "../codec/CodecInterface.hpp"

#define USB_AUDIO_PRIO  10  
#define USB_AUDIO_CORE  1

namespace AudioUSB {
    void initialize();
    bool isActive();
    void dump_info();
    void compile();
    void read(float stream[SAMPLING_CHANNELS][SAMPLING_FRAME]);
    void write(float stream[SAMPLING_CHANNELS][SAMPLING_FRAME]);
}