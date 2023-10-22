#pragma once
#include "Node.hpp"
#include <string>

class NodeControl : public Node {
protected:
	Node * reference;

public:
	NodeControl(Node* parent, const char* name, const char* displayName, Node * reference);

	const char* getType();

	void edit(bool dir);
    virtual void * getStorageData(int * length) = 0;
    virtual const char * getSource() = 0;
	virtual bool fromString(std::string value) = 0;
	virtual std::string toString() = 0;
	virtual std::string getValueJSON() = 0;
	std::string getDescriptionJSON();
};

