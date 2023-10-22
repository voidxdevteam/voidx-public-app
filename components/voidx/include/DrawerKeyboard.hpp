#pragma once
#include "Event.hpp"
#include <string>

#define STR_KEY_MAX_LEN 20
class DrawerKeyboard: public Listener {
private:
    std::string * str;
    std::string temp;
    std::string title;
    int cursor;
    int blink_cursor;
    int shift;
public:
    DrawerKeyboard(std::string title, std::string * str);
    bool draw();
    bool onEvent(int event);
};
