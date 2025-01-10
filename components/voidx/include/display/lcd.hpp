#include "glcd.h"
#include "../driver/i2c_bus.h"

namespace LCD {
    void initialize();
    void splash();
    void set_custom_splash(void (*func)(void));
}



