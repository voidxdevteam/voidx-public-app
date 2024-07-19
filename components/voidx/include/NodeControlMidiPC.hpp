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
	//! NodeControlMidiPC constructor
    /*!
      \param parent parent of this Node.
      \param name name of this Node.
      \param displayName label to be displayed for this Node.
      \param reference reference NodeParList to be switched through this MidiPC controller.
      \param first_address default first PC address for starting MIDI PC indexing the elements of the NodeParList at first run.
      \param midi_address NodeEnum that allows the user to select the MIDI channel of the device. It is a NodeEnum containing channel numbers as options (e.g. "0","1", "2",...). 
					      If this parameter contains "0" as item, the first MIDI address is considered as 0, otherwise 1.
    */
	NodeControlMidiPC(Node* parent, const char* name, const char* displayName, NodeParList * reference, int first_address, NodeEnum * midi_address);

	void fromSource(unsigned char * data, int length);

	void onLoad();
	void * getStorageData(int * length);
	bool fromString(std::string value);
	std::string toString();
	std::string getValueJSON();

};

