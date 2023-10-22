#ifdef __cplusplus
extern "C" {
#endif

#include "driver/spi_master.h"
#include "esp_types.h"
#include "esp_err.h"
#include "esp_check.h"
#include "driver/gpio.h"

esp_err_t spi_initialize();
spi_bus_config_t * spi_get_conf();

#ifdef __cplusplus
}
#endif