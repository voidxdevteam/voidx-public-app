#pragma once
#include "esp_log.h"
#include "esp_timer.h"
#include "utils.hpp"
#include "../driver/io.h"
#include "../driver/io_array.hpp"
#include <list>

//! Listener class to send/receive user events
/*!
  A Listener object has 2 main purposes:
  - receive user events;
  - send info to the user through an output interface (i.e. an LCD display)
*/
class Listener {
private:
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
   bool hasFocus(Listener * listener);
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

#define INACTIVITY_TIMEOUT_S	30

#define INACTIVITY(val, on_inactivity) {\
		static int old_val = val;\
		static int timer = 0;\
		if(old_val != val) timer = 0;\
		else timer++;\
		if(timer > IOArray::ms_to_tick(INACTIVITY_TIMEOUT_S*1000)) {on_inactivity; timer=0;} \
	}

#define ENCODER_STD_DEBOUNCE 		1
#define ENCODER_IO_ARRAY_DEBOUNCE 	-1
#define ENCODER_STOP_DURATION_MS	2000

#define ENCODER(a, b, up, down, steps, debounce_ms) {\
		int new_ab_value = a * 2 + b;\
		static int timer_counter = 0;\
		static uint64_t timer = esp_timer_get_time();\
		static uint64_t pause_timer = esp_timer_get_time();\
		static int raw_enc_value = 0;\
		static int old_ab_value = new_ab_value;\
		if(new_ab_value != old_ab_value) pause_timer = esp_timer_get_time();\
		else if(esp_timer_get_time() - pause_timer > MSEC_TO_USEC(ENCODER_STOP_DURATION_MS)) pause_timer = esp_timer_get_time() - MSEC_TO_USEC(ENCODER_STOP_DURATION_MS);\
		if(debounce_ms >= 0){\
			if(new_ab_value != old_ab_value && (esp_timer_get_time() - pause_timer) < MSEC_TO_USEC(debounce_ms)) new_ab_value = old_ab_value;\
			else timer = esp_timer_get_time();\
		} else {\
			if(new_ab_value != old_ab_value && timer_counter++ < IOArray::ms_to_tick(-debounce_ms)) new_ab_value = old_ab_value;\
			else timer_counter = 0;\
		}\
		int ab_out = QEM [old_ab_value * 4 + new_ab_value];\
		if((old_ab_value ^ new_ab_value) == 0b11 || (esp_timer_get_time() - pause_timer) >= MSEC_TO_USEC(ENCODER_STOP_DURATION_MS)) { raw_enc_value = 0; }\
		else raw_enc_value += ab_out;\
		old_ab_value = new_ab_value;\
		if(raw_enc_value > 2){\
			raw_enc_value -=4;\
			for(int si = 0; si<steps; si++) up;\
		}\
		else if(raw_enc_value < -2){\
			raw_enc_value += 4;\
			for(int si = 0; si<steps; si++) down;\
		}\
	}

#define LONG_PRESS_DURATION_MS	1500
#define PRESS(in, press, release, longPress, longRelease) {\
		static int prev_status = in;\
		static int status = in;\
		static uint64_t debounce = esp_timer_get_time();\
		static uint64_t timer = esp_timer_get_time();\
		static int initial_status = in;\
		static int longPress_enabled = 0;\
		if(in == status) debounce = esp_timer_get_time();\
		else if((esp_timer_get_time() - debounce) > MSEC_TO_USEC(50)) {status = in; }\
		if((esp_timer_get_time() - timer) > MSEC_TO_USEC(LONG_PRESS_DURATION_MS*2)) timer = esp_timer_get_time() - MSEC_TO_USEC(LONG_PRESS_DURATION_MS*2);\
		if(status != initial_status && (esp_timer_get_time() - timer) > MSEC_TO_USEC(LONG_PRESS_DURATION_MS)) {if(longPress_enabled) {longPress; longPress_enabled = 0;}}\
		if(status != prev_status){\
			if(status != initial_status) {press;}\
			if(status == initial_status) {\
				if((esp_timer_get_time() - timer) < MSEC_TO_USEC(LONG_PRESS_DURATION_MS)) {release;}\
				else {longRelease;}\
			}\
			prev_status = status;\
			timer = esp_timer_get_time();\
		}\
		if(status == initial_status){timer = esp_timer_get_time(); longPress_enabled = 1;}\
	}

static const int QEM [16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

#define EVENT_DRAW          		1
#define EVENT_REMOVE        		2
#define EVENT_INACTIVITY        	3
#define EVENT_ENC_UP        		10
#define EVENT_ENC_DOWN      		11
#define EVENT_ENC_PRESSED   		12
#define EVENT_ENC_RELEASED  		13
#define EVENT_ENC_LONG_PRESSED  	14
#define EVENT_ENC_LONG_RELEASED  	15
#define EVENT_FSW_PRESSED   		16
#define EVENT_FSW_RELEASED  		17
#define EVENT_FSW_LONG_PRESSED  	18
#define EVENT_FSW_LONG_RELEASED  	19
#define EVENT_TIMER_200MS   		20
#define EVENT_NEXT					30
#define EVENT_PREV					31
#define EVENT_ENC2_UP        		40
#define EVENT_ENC2_DOWN      		41
#define EVENT_ENC2_PRESSED   		42
#define EVENT_ENC2_RELEASED  		43
#define EVENT_ENC2_LONG_PRESSED  	44
#define EVENT_ENC2_LONG_RELEASED  	45
#define EVENT_INPUT					64

#define EVENT_TIME_MS   (10)
#define EVENT_MS(x)     (x / EVENT_TIME_MS)

void waitModal();
void system_tasks(void * parametr);
void event_tasks(void * parameter);
