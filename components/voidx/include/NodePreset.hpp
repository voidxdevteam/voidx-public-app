#pragma once
#include "NodeParList.hpp"
#include "NodeList.hpp"

#define DEFAULT_PRESET_NAME	"new preset"

class NodePreset: public NodeParList {
private:
	std::list<Node *> ignore;
public:
	NodePreset(Node* parent, const char* name, const char* displayName, std::string value, NodeList * reference);
	void onLoad();
	bool isEdited();
	bool isEditable();
	bool setByIndex(int index);
	bool setValue(std::string value);
	void saveAs(int slot, std::string name);

	void setPresetAt(int index, std::string name, char * data);

	void setIgnoreNode(Node * node, bool ignore);
	void addIgnoreNode(Node * node);
	void removeIgnoreNode(Node * node);

	std::string presetToString();
};
