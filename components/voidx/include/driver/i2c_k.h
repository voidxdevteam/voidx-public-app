#ifdef __cplusplus
extern "C" {
#endif

#include "esp_check.h"
#include "driver/i2c.h"
#include "esp_types.h"
#include "esp_err.h"


/* I2C port and GPIOs */
#define I2C_NUM         ((i2c_port_t)0)
#ifdef CONFIG_IDF_TARGET_ESP32C3
#define I2C_SDA_IO      (GPIO_NUM_16)
#define I2C_SCL_IO      (GPIO_NUM_15)
#else
#define I2C_SDA_IO      (GPIO_NUM_16)
#define I2C_SCL_IO      (GPIO_NUM_15)
#endif

esp_err_t i2c_initialize();
i2c_config_t * i2c_get_conf();

#ifdef __cplusplus
}
#endif