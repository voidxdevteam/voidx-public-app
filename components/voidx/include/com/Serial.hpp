#pragma once
#include "ComInterface.hpp"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "soc/uart_channel.h"

class Serial: public ComInterface {
private:
    int uart_tx;
    int uart_rx;
    uart_port_t uart_port;
    uart_config_t uart_config;
    char * data;
    int buffer_size;
    int data_size;
    bool initialized;
    std::string response;
public:
	Serial(Node * root, uart_port_t uart_port, int uart_tx, int uart_rx);
	void initialize();
	void tasks();
	virtual ~Serial(){};
};
