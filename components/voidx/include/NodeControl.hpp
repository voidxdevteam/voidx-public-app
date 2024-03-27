#pragma once
#include "Node.hpp"
#include <string>
#include <cstring>

class NodeControl : public Node {
protected:
	Node * reference;
	const char * source;
	const char * source_type;

public:
	NodeControl(Node* parent, const char* name, const char* displayName, Node * reference, const char * source, const char * source_type);

	const char* getType();
	
	void edit(bool dir);

    const char * getSource();
	const char * getSourceType();
	virtual void fromSource(unsigned char * data, int length) = 0;

    virtual void * getStorageData(int * length) = 0;
	virtual bool fromString(std::string value) = 0;
	virtual std::string toString() = 0;
	virtual std::string getValueJSON() = 0;
	std::string getDescriptionJSON();
};

