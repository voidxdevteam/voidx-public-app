idf_component_register(INCLUDE_DIRS "include"
                                 "include/controller"
                                 "include/dsp"
                                 "include/codec"
                                 "include/dsp/libs"
                                 "include/driver"
                                 "include/display"
                                 "include/driver/update"
                                 "include/com"
                    REQUIRES driver spi_flash esp_timer nvs_flash esp_wifi bt esp_partition app_update esp-tls mdns esp-dsp usb LDFRAGMENTS "linker_usb.lf")
add_prebuilt_library(kore "libvoidx.a" REQUIRES driver spi_flash esp_timer nvs_flash esp_wifi bt esp_partition app_update esp-tls espressif__mdns espressif__esp-dsp usb)
add_prebuilt_library(libusb "libvoidx__tinyusb.a" REQUIRES driver spi_flash esp_timer nvs_flash esp_wifi bt esp_partition app_update esp-tls espressif__mdns espressif__esp-dsp usb)

target_link_libraries(${COMPONENT_LIB} INTERFACE kore)
target_link_libraries(${COMPONENT_LIB} INTERFACE libusb)