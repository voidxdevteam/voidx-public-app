#include "Node.hpp"
#include "Event.hpp"

#define VISIBLE_ITEMS 4

class DrawerSetup: public Listener {
private:
    std::vector<Node *> nodes;
    int cursor;
    int slide;
    int viewCursor;
    int itemCount;
public:
    DrawerSetup();
    bool draw();
    bool onEvent(int event);
};
