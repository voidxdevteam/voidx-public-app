#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "glcd.h"

#include "../driver/i2c_k.h"

void lcd_initialize();
void lcd_splash();

#ifdef __cplusplus
}
#endif
