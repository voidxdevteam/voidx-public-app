#include "Event.hpp"
#include <stdio.h>

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