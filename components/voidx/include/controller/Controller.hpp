#pragma once
#include "../NodeControl.hpp"
#include <cstring>
#include <set>

class Controller {
private:
	const char * name;
	std::set<NodeControl *> controllers;

public:
	Controller(const char * name);
	bool operator<(const Controller &c) const { return strcmp(this->name, c.name); };
};
