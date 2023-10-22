#ifdef __cplusplus
extern "C" {
#endif

#include "spi.h"
#include "driver/spi_master.h"

#define IO_FREQ		100000
#define IO_SPEED	(IO_FREQ / 8)
#define IO_MS(x)	(((x)*(IO_SPEED))/(1000))

#define IO_MAX_IN   4
#define IO_MAX_OUT  8

#define IO_PWM_DISABLE -1
#define PWM_MAX_VALUE	128

#define IO_OUT_LED_BLUE 	2
#define IO_OUT_LED_GREEN 	7
#define IO_OUT_LED_RED 		4

//must be a power of 2
#define IO_QUEUE_SIZE		256

void io_initialize();
void io_tasks();
bool io_has_data();
int io_in_get(int index);
void io_out_set(int index, int value);
void io_pwm_set(int index, int value);

#ifdef __cplusplus
}
#endif
