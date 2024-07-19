#include "esp_system.h"
#include "esp_log.h"

#pragma once

namespace Time {
    void initialize();
    bool hasTime();
    void tasks();
    //return us since epoch
    int64_t getTime();
}
