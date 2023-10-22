#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../Node.hpp"
#include "../NodeList.hpp"

#define COM_PACKET_SIZE	1500
#define COM_TIME_MS	10

class ComInterface {
private:
	Node * root;
protected:
	std::string processRequest(std::string request);
public:
	virtual void initialize(){};
	virtual void tasks(){};
	ComInterface(Node * root);
	virtual ~ComInterface(){};
};

namespace Com
{
	void initialize();
    void com_tasks(void * par);
}
