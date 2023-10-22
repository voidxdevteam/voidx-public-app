#pragma once
#include "Event.hpp"
#include <string>
#include <vector>

#define VISIBLE_ITEMS 4

class DrawerChooser: public Listener {
private:
    int cursor;
    int slide;
    int viewCursor;
    int itemCount;
    std::string * str;
    std::string title;
    std::vector<std::string> items;
public:
    DrawerChooser(std::string title, std::vector<std::string> items, std::string * str);
    bool draw();
    bool onEvent(int event);
};
