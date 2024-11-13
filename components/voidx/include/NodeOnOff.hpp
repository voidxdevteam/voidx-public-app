#pragma once
#include "NodeEnum.hpp"

class NodeOnOff : public NodeEnum {
private:

public:
	static inline const char * ON = "ON";
	static inline const char * OFF = "OFF";

	NodeOnOff(Node* parent, const char* displayName, std::string value);
	
	void edit(bool dir);
};
