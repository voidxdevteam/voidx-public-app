#include "Event.hpp"
#include <stdio.h>
#pragma once

namespace Board {
    void initialize();
    void eventLoop();
}

class Bsp {
private:
public:
    Bsp();
    virtual void initialize() = 0;
    virtual void eventLoop() = 0;
};