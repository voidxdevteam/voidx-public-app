#pragma once
#include "Node.hpp"

namespace License {
	void initialize(Node * parent, const char * license);
	bool getStatus();
	char * getID(); 
	unsigned char * getMAC();
	char * getMAC_str();
}
