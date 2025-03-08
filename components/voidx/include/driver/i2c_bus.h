#ifdef __cplusplus
extern "C" {
#endif

#include "esp_check.h"
#include "driver/i2c_master.h"
#include "esp_types.h"
#include "esp_err.h"


/* I2C port and GPIOs */
#define I2C_NUM         ((i2c_port_t)0)
#define I2C_SDA_IO      (GPIO_NUM_16)
#define I2C_SCL_IO      (GPIO_NUM_15)

esp_err_t i2c_initialize();
void i2c_set_io(gpio_num_t sda, gpio_num_t scl);
i2c_master_bus_handle_t i2c_get_handle();

#ifdef __cplusplus
}
#endif