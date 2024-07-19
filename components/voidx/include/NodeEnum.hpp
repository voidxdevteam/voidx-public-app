#pragma once
#include "Node.hpp"
#include <vector>

class NodeEnum : public Node {
private:
	std::string value;
	std::string defaultValue;
	std::vector<const char *> elms;

public:
	NodeEnum(Node* parent, const char* name, const char* displayName, std::vector<const char *> elms, std::string value);

	const char* getType();

	bool isValue(const char * val);
	void edit(bool dir);
	void toggle();
	void setValue(std::string value);
	
    //! Verify if a NodeEnum contains a specific option
    /*!
      \param option name of the option   
      \return the test result: true if option is a possible value of the NodeEnum
    */
	bool hasValue(std::string option);
    void * getStorageData(int * length);
	std::string toString();
	bool fromString(std::string value);
	std::string getValueJSON();
	std::string getDescriptionJSON();
};
