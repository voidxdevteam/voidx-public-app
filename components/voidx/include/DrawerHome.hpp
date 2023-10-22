#pragma once
#include "Node.hpp"
#include "NodePreset.hpp"
#include "Event.hpp"

class DrawerHome: public Listener {
private:
    Node * node;
    Node * sys;
    NodePreset * pres;
    int cursor;
    int viewCursor;
    int slide;
public:
    DrawerHome(Node * node, Node * sys, NodePreset * pres);
    void setNodes(Node * node, Node * sys, NodePreset * pres);
    bool draw();
    bool onEvent(int event);
};
