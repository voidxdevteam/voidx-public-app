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
    std::string version;
public:
    DrawerHome(Node * node, Node * sys, NodePreset * pres);
    void setNodes(Node * node, Node * sys, NodePreset * pres);
    void setVersion(std::string version);
    bool draw();
    bool onEvent(int event);
};
