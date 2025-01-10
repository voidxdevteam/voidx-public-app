#ifdef __cplusplus
extern "C" {
#endif

#include "esp_check.h"
#include "driver/i2c.h"
#include "esp_types.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "esp_adc/adc_oneshot.h"

#define ADC_UP_DOWN(data, debounce_ms, on_up, on_down){\
		int value = data;\
		static int old_status = 0;\
		static int64_t time = esp_timer_get_time();\
		int status = 0;\
		if(value < 1000) status = 2;\
		else if(value < 3000) status = 1;\
		if(old_status == status) time = esp_timer_get_time();\
		else if(time > (1000*debounce_ms)){\
			old_status = status;\
			if(status == 1) {on_up;}\
			if(status == 2) {on_down;}\
		}\
	}

int adc_read(adc_unit_t unit, adc_channel_t channel);

#ifdef __cplusplus
}
#endif