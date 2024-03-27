#pragma once
#include "NodeControl.hpp"
#include "NodeParList.hpp"
#include "NodeEnum.hpp"
#include <string>

class NodeControlMidiPC : public NodeControl {
private:
	int * elements;
	int n_elements;
	bool check_value(std::string s, bool read);
	NodeEnum * midi_address;

public:
	NodeControlMidiPC(Node* parent, const char* name, const char* displayName, NodeParList * reference, int first_address, NodeEnum * midi_address);

	void fromSource(unsigned char * data, int length);

	void onLoad();
	void * getStorageData(int * length);
	bool fromString(std::string value);
	std::string toString();
	std::string getValueJSON();

};

