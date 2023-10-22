#pragma once
#include "NodeControl.hpp"
#include "NodeParList.hpp"
#include <string>

#define SOURCE_MIDI_PC "midipc"

class NodeControlMidiPC : public NodeControl {
private:
	int * elements;
	int n_elements;
	bool check_value(std::string s, bool read);

public:
	NodeControlMidiPC(Node* parent, const char* name, const char* displayName, NodeParList * reference, int first_address);

	void onLoad();
	void * getStorageData(int * length);
	bool fromString(std::string value);
	std::string toString();
	std::string getValueJSON();

	const char * getSource(){ return SOURCE_MIDI_PC; };
};

