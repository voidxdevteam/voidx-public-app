#pragma once
#include "Node.hpp"
#include "NodeItem.hpp"

#define COMMUNICATION_STATUS_IDLE -1
#define COMMUNICATION_MAX_SIZE	256

#define APP_NAME 		"VoidX Device"
#define APP_AUTHOR		"VoidX team"
#define APP_VERSION		"1.0"
#define APP_LICENSE				"ap0003"
#define APP_PUBLIC_LICENSE		"common"
#define APP_LOGO		""

namespace System {
	void initialize(const char * license);
	Node* appNode();
	Node* rootNode();
	Node* systemNode();
	std::string getName();
	char * getID();
}
