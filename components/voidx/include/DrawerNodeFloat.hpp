#pragma once
#include "Node.hpp"
#include "NodeFloat.hpp"
#include "NodeEnum.hpp"
#include "Event.hpp"

//! Listener that draws a as Popup a NodeFloat
/*!
  Useful Listener to show a temporary popup to view the status of a NodeFloat on screen.
*/
class DrawerNodeFloat: public Listener {
private:
    NodeFloat * node;
    NodeEnum * toggle;
    int event_up;
    int event_down;
    int timeout_s;
    int elapsed;
    std::string title;
    int toggle_event;
    std::string toggle_on;
public:
    //! DrawerNodeFloat constructor
    /*!
      \param node the node that will be displayed.
      \param event_up the event that causes the node increment
      \param event_down the event that causes the node decrement
      \param timeout_s timeout (in seconds) of the popup. This Listener will be automatically removed from stack 
      neither event_up nor event_down are triggered for the defined timeout.
      \param title title of the popup
      \param toggle (optional) NodeEnum that can show the related status of a parameter i.e. enabled or not
      \param toggle_event (optional) event that trigger a change in toggle NodeEnum
      \param toggle_on (optional) toggle on string value
    */
    DrawerNodeFloat(NodeFloat * node, int event_up, int event_down, int timeout_s, std::string title, NodeEnum * toggle = NULL, int toggle_event = -1, std::string toggle_on = "");

    bool draw();
    bool onEvent(int event);
};
