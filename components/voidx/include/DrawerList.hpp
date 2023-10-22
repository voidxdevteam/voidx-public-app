#include "Node.hpp"
#include "NodeParList.hpp"
#include "Event.hpp"

#define VISIBLE_ITEMS 4

class DrawerList: public Listener {
private:
    NodeParList * node;
    NodeList * list;
    int cursor;
    int slide;
    int viewCursor;
    int itemCount;
public:
    DrawerList(NodeParList * node);
    void setNode(NodeParList * node);
    bool draw();
    bool onEvent(int event);
};
