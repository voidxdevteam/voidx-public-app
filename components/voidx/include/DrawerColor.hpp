#pragma once
#include "Event.hpp"
#include <string>

class DrawerColor: public Listener {
private:
    std::string * str;
    std::string temp;
    std::string title;
    int color;
    int cursor;
    int blink_cursor;
    int shift;
    void updateColor();
public:
    DrawerColor(std::string title, std::string * str);
    bool draw();
    bool onEvent(int event);
};
