#pragma once
#include "Node.hpp"

#define NODE_ITEM_TYPE_STRING 	"string"
#define NODE_ITEM_TYPE_SYSTEM 	"system"
#define NODE_ITEM_TYPE_COLOR 	"color"
#define NODE_ITEM_TYPE_HFOLDER 	"hfolder"
#define NODE_ITEM_TYPE_VFOLDER 	"vfolder"
#define NODE_ITEM_TYPE_MODULE 	"module"

class NodeItem : public Node {
private:
	std::string value;
	const char* itemType;

public:
	NodeItem(Node* parent, const char* name, const char* displayName, std::string value, const char * itemType);

	const char* getType();
	std::string getValue();
	bool setValue(std::string value);

	void edit(bool dir);
    void * getStorageData(int * length);
	std::string toString();
	bool fromString(std::string value);
	std::string getValueJSON();
	std::string getDescriptionJSON();

	const char* getItemType();
};
