#pragma once
#include "Event.hpp"
#include <string>

#define POPUP_NOTIFY    0
#define POPUP_CONFIRM   1
#define POPUP_SAVE_DISCARD 2

class DrawerPopup: public Listener {
private:
    std::string str1;
    std::string str2;    
    int cursor;
    int type;
    int * result;
    bool pressed;

public:
    DrawerPopup(std::string str1, std::string str2, int type, int * result);
    bool draw();
    bool onEvent(int event);
};
