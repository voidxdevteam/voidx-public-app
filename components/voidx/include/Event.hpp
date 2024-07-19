#pragma once
#include "utils.hpp"
#include "../driver/io.h"
#include "../driver/io_array.hpp"
#include <list>

class Listener {
public:
    Listener();
    virtual ~Listener(){};
    virtual bool draw() = 0;
    virtual bool onEvent(int event) = 0;
    virtual void onBroadcast(int event) {};
};

namespace EventDispatcher
{
   void addEvent(int event);
   bool dispatch();
   int elements();
   void broadcast(int event);
}

#define TIMER_TON(input, time_ms, exec){\
		static unsigned int time_status;\
		if(input){\
			if((xthal_get_ccount()-time_status) > (time_ms * 1000 * CCT_TICKS_PER_US)){\
				exec;\
			}\
		} else {\
			time_status = xthal_get_ccount();\
		}\
	}


#define ENCODER(a, b, up, down, steps) {\
		int new_ab_value = a * 2 + b;\
		static int raw_enc_value = 0;\
		static int old_ab_value = new_ab_value;\
		int ab_out = QEM [old_ab_value * 4 + new_ab_value];\
		old_ab_value = new_ab_value;\
		raw_enc_value += ab_out;\
		if(raw_enc_value > 2){\
			raw_enc_value -=4;\
			for(int si = 0; si<steps; si++) up;\
		}\
		else if(raw_enc_value < -2){\
			raw_enc_value += 4;\
			for(int si = 0; si<steps; si++) down;\
		}\
	}

#define PRESS(in, press, release, longRelease) {\
		static int old_push_value = in;\
		static int debounce = 0;\
		if(debounce++ > IOArray::ms_to_tick(5000)) debounce = IOArray::ms_to_tick(5000);\
		if(debounce > IOArray::ms_to_tick(100) && in != old_push_value){\
			if(old_push_value == 1) {press;}\
			if(old_push_value == 0) {\
				if(debounce < IOArray::ms_to_tick(1000)) {release;}\
				else {longRelease;}\
			}\
			old_push_value = in;\
			debounce = 0;\
		}\
	}

static const int QEM [16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

#define EVENT_DRAW          		1
#define EVENT_REMOVE        		2
#define EVENT_ENC_UP        		10
#define EVENT_ENC_DOWN      		11
#define EVENT_ENC_PRESSED   		12
#define EVENT_ENC_RELEASED  		13
#define EVENT_ENC_LONG_RELEASED  	14
#define EVENT_FSW_PRESSED   		15
#define EVENT_FSW_RELEASED  		16
#define EVENT_FSW_LONG_RELEASED  	17
#define EVENT_TIMER_200MS   		20
#define EVENT_NEXT					30
#define EVENT_PREV					31
#define EVENT_ENC2_UP        		40
#define EVENT_ENC2_DOWN      		41
#define EVENT_ENC2_PRESSED   		42
#define EVENT_ENC2_RELEASED  		43
#define EVENT_ENC2_LONG_RELEASED  	44
#define EVENT_INPUT					64

#define EVENT_TIME_MS   (10)
#define EVENT_MS(x)     (x / EVENT_TIME_MS)

void waitModal();
void system_tasks(void * parametr);
void event_tasks(void * parameter);
