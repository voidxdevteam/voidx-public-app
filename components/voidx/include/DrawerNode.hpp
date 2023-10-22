#include "Node.hpp"
#include "Event.hpp"

#define VISIBLE_ITEMS 4

class DrawerNode: public Listener {
private:
    Node * node;
    int cursor;
    int slide;
    int viewCursor;
    int itemCount;
    Node * nodeSelected;
public:
    DrawerNode(Node * node);
    void setNode(Node * node);
    bool draw();
    bool onEvent(int event);
};
