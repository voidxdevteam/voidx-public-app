#pragma once
#include "Event.hpp"
#include <string>

class DrawerFastNodes: public Listener {
private:
    float val_bar;
public:
    DrawerFastNodes();
    bool draw();
    bool onEvent(int event);
};
