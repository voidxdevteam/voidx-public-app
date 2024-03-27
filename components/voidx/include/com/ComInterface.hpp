#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../Node.hpp"
#include "../NodeList.hpp"
#include "esp_timer.h"

#define COM_PACKET_SIZE	1500
#define COM_TIME_MS	10

class ComInterface {
private:
	Node * root;
	std::string last_token;
	int64_t read_time;
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
