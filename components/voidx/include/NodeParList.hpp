#pragma once
#include "Node.hpp"
#include "NodeList.hpp"

class NodeParList : public Node {
protected:
	std::string value;
	NodeList * reference;

public:
	NodeParList(Node* parent, const char* name, const char* displayName, std::string value, NodeList* reference);

	const char* getType();

	NodeList * getReferenceList();
	char * getData();
	std::string getValue();
	int getElementCount();
	int getIndex();
	virtual bool isEditable();
	virtual bool setValue(std::string value);

	void edit(bool dir);
	bool canEdit(bool dir);
    void * getStorageData(int * length);
	bool fromString(std::string value);
	std::string toString();
	std::string getValueJSON();
	std::string getDescriptionJSON();
};
