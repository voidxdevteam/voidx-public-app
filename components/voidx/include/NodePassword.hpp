#pragma once
#include "NodeItem.hpp"

class NodePassword : public NodeItem {
private:

public:
	NodePassword(Node* parent, const char* name, const char* displayName, std::string value, const char * itemType);
	std::string getValue();
};
