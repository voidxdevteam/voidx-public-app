/*
 * SPDX-FileCopyrightText: 2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */
//#include <kore.hpp>
#include <stdio.h>
#include <string.h>
#include "esp_heap_caps.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s.h"
#include "driver/gpio.h"
#include "driver/io.h"
#include "driver/io_array.hpp"
#include "driver/uart.h"
#include "esp_system.h"
#include "esp_check.h"
#include "driver/update/update.hpp"
#include "esp_dsp.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "driver/i2c.h"
#include "System.hpp"
#include "Event.hpp"
#include "debug.hpp"
#include "DrawerNode.hpp"
#include "app/IrLoaderStereo.hpp"
#include "app/Eq7.hpp"
#include "codec/CodecInterface.hpp"
#include "dsp/AudioProcessor.hpp"
#include "bsp/MiniStompX.hpp"
#include "com/Bluetooth.hpp"
#include "com/Wifi.hpp"
#include "com/Serial.hpp"

static void system_info(void * ptr){
    while(1){
        //char buffer[2048];
        //vTaskList(buffer);
        //puts(buffer);
        //ESP_LOGW("cycle ", "%d / %d max %d", Debug::getExecTicks(), Debug::getCycleTicks(), Debug::getMaxExecTicks(true));
        vTaskDelay(2000 / portTICK_PERIOD_MS);
		#ifdef DEBUG_HEAP
        //heap_caps_print_heap_info(MALLOC_CAP_DEFAULT);
        int bytesFree = heap_caps_get_free_size(MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
		ESP_LOGW("Mem", "%zu MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM bytes free.", bytesFree);
		bytesFree = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
		ESP_LOGW("Mem", "%zu MALLOC_CAP_INTERNAL bytes free.", bytesFree);
		#endif
    }
}

extern "C"
void app_main(void)
{
    System::initialize();

    /* Choose peripherals */ 
    new Wifi(System::rootNode(), System::rootNode()->pathToNode("root\\sys\\_name"), 8080);
    new Bluetooth(System::rootNode(), System::rootNode()->pathToNode("root\\sys\\_name"));
    new Serial(System::rootNode(), UART_NUM_0, UART_NUM_0_TXD_DIRECT_GPIO_NUM, UART_NUM_0_RXD_DIRECT_GPIO_NUM);

    /* Start the application */
    new Eq7(System::appNode(), System::rootNode(), System::systemNode());

	AudioProcessor::audioInitialize(System::systemNode());
    
    /* Start relevant tasks */
    xTaskCreatePinnedToCore(system_tasks, "systemTasks", 8192, NULL, 4, NULL, 0);
    xTaskCreatePinnedToCore(event_tasks, "eventTasks", 8192, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(system_info, "infoTasks", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(Com::com_tasks, "comTasks", 1024*16, NULL, 6, NULL, 0);
}
