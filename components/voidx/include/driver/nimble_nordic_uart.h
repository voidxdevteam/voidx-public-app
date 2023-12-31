#include <stdint.h>

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/ringbuf.h>
#include <host/ble_hs.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_NORDIC_UART_MAX_LINE_LENGTH 4096
#define CONFIG_NORDIC_UART_RX_BUFFER_SIZE 8192

extern RingbufHandle_t nordic_uart_rx_buf_handle;

enum nordic_uart_callback_type {
  NORDIC_UART_DISCONNECTED,
  NORDIC_UART_CONNECTED,
};

typedef void (*uart_receive_callback_t)(struct ble_gatt_access_ctxt *ctxt);

esp_err_t nordic_uart_start(const char *device_name, void (*callback)(enum nordic_uart_callback_type callback_type));
void nordic_uart_stop(void);
int nordic_uart_get_connection_status();

esp_err_t nordic_uart_send(const char *message, char eol);
esp_err_t nordic_uart_sendln(const char *message);
esp_err_t nordic_uart_yield(uart_receive_callback_t uart_receive_callback);

// private funcs for testing.
esp_err_t _nordic_uart_buf_deinit();
esp_err_t _nordic_uart_buf_init();
esp_err_t _nordic_uart_send_line_buf_to_ring_buf();
esp_err_t _nordic_uart_linebuf_append(char c);
bool _nordic_uart_linebuf_initialized();

esp_err_t _nordic_uart_start(const char *device_name, void (*callback)(enum nordic_uart_callback_type callback_type));
void _nordic_uart_stop(void);
esp_err_t _nordic_uart_send(const char *message, char eol);

#ifdef __cplusplus
}
#endif
