#pragma once
#include "../NodeControl.hpp"
#include <cstring>
#include <map>
#include <set>

class Source {
private:
	const char * name;
	std::set<NodeControl *> controllers;

public:
	Source(const char * name);

	const char * getName(){ return this->name; };
	void addController(NodeControl * controller);
	virtual void tasks(){};
	void send(unsigned char * data, int length);
};

namespace Control {
	void addSource(Source * c);
	Source * getSource(const char * name);
	void linkSource(const char * name, NodeControl * controller);
	void tasks();
}
