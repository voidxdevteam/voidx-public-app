#include "esp_system.h"
#include "esp_log.h"

#pragma once

#define CPU_FREQ_MHZ 240

namespace Debug {
    extern unsigned int time;
    void cycle_start();
    void cycle_measure();
    unsigned int get_overrun_cnt();
    unsigned int getCycleTicks();
    unsigned int getExecTicks();
    unsigned int getMaxExecTicks(bool reset);
}

//#define DEBUG_MESSAGES
//#define DEBUG_PRESETS
#define DEBUG_HEAP
//#define DEBUG_STORAGE
//#define DEBUG_NOTIFY
//#define DEBUG_COM
