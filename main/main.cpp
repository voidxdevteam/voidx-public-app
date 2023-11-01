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
#include "display/lcd.hpp"
#include "app/IrLoaderStereo.hpp"
#include "app/Eq7.hpp"
#include "dsp/AudioProcessor.hpp"
#include "codec/CodecInterface.hpp"
#include "com/Bluetooth.hpp"
#include "com/Wifi.hpp"

static void system_info(void * ptr){
    while(1){
        //vTaskList(buffer);
        //puts(buffer);
        //ESP_LOGW("cycle ", "%d / %d max %d", Debug::getExecTicks(), Debug::getCycleTicks(), Debug::getMaxExecTicks(true));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
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
    //io_initialize();
    IOArray::initialize(8, 4000, 100, 32);
    //update_initialize();
    Codec::initialize();
    System::initialize();
    //lcd must be started after codec
    lcd_initialize();
    //func();
    
    new Wifi(System::rootNode(), System::rootNode()->pathToNode("root\\sys\\_name"), 8080);
    new Bluetooth(System::rootNode(), System::rootNode()->pathToNode("root\\sys\\_name"));

    //new DigitalChorus(System::appNode());
    //new DualAxis(System::appNode());
    //new Tuner(System::appNode(), System::rootNode(), System::systemNode());
    new IrLoaderStereo(System::appNode(), NULL);

	AudioProcessor::audioInitialize(System::systemNode());
    //Com::initialize();
    //xTaskCreate(testStorage, "storeTask", 5000, NULL, 2, NULL);
    xTaskCreatePinnedToCore(system_tasks, "systemTasks", 8192, NULL, 4, NULL, 0);
    xTaskCreatePinnedToCore(event_tasks, "eventTasks", 8192, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(system_info, "infoTasks", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(Com::com_tasks, "infoTasks", 1024*16, NULL, 6, NULL, 0);
    //xTaskCreatePinnedToCore(midiTask, "midiTask", 8192, NULL, 3, NULL, 0);
}
