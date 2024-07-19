#pragma once
#include "Controller.hpp"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "soc/uart_channel.h"

#define SOURCE_MIDI "midi"
#define SOURCE_TYPE_MIDI_PC "pc"
#define SOURCE_EXPR "expr"

class SourceMidi: public Source {
    static const int MIDI_BUFFER_LENGTH = 6;
private:
    gpio_num_t uart_tx;
    gpio_num_t uart_rx;
    uart_port_t uart_port;
    uart_config_t uart_config;
	int buffer_size;
    char * data;
    unsigned char midi_buffer[MIDI_BUFFER_LENGTH];
    int midi_buffer_index;
    int midi_message_type;
    int midi_message_channel;
	bool initialized;

public:
    static const int MIDI_PROGRAM_CHANGE = 4;
    static const int MIDI_PROGRAM_CHANGE_LENGTH = 2;

	SourceMidi(const char * name, uart_port_t uart_port, int uart_tx, int uart_rx);
	void initialize();
	void tasks();
};
