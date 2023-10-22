#pragma once
#include "Node.hpp"
#include "NodeItem.hpp"

#define COMMUNICATION_STATUS_IDLE -1
#define COMMUNICATION_MAX_SIZE	256

#define APP_NAME 		"VoidX IR LOADER"
#define APP_AUTHOR		"VoidX team"
#define APP_VERSION		"1.0"
#define APP_LICENSE		"ap0003"
#define APP_LOGO		"https://icones.pro/wp-content/uploads/2021/04/symbole-apple-icone-logo-orange.png"

namespace System {
	void initialize();
	Node* appNode();
	Node* rootNode();
	Node* systemNode();
	std::string getName();
	char * getID();
}
