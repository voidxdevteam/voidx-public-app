#pragma once
#include "NodeControl.hpp"
#include "NodeParList.hpp"
#include "NodeEnum.hpp"
#include <string>

class NodeControlExp : public NodeControl {
private:
	int channel;
public:
	NodeControlExp(Node* parent, const char* name, const char* displayName, int channel);

	std::string toString();
	std::string getValueJSON();

};

