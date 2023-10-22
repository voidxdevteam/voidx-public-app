#pragma once
#include "ComInterface.hpp"

class Bluetooth: public ComInterface {
private:
	Node * devName;
public:
	Bluetooth(Node * root, Node * devName);
	void initialize();
	void tasks();
	virtual ~Bluetooth(){};
};
