#pragma once
#include "NodeParList.hpp"
#include "NodeList.hpp"

#define DEFAULT_PRESET_NAME	"new preset"

class NodePreset: public NodeParList {
public:
	NodePreset(Node* parent, const char* name, const char* displayName, std::string value, NodeList * reference);
	void onLoad();
	bool isEditable();
	bool setValue(std::string value);
	void saveAs(int slot, std::string name);
};
