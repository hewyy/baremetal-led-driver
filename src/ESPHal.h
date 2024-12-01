#ifndef ESPHAL_H
#define ESPHAL_H

#include <stdint.h>

class ESPHal {
public:
    static void configureOutput(uint32_t gpio_num);
    static void setHigh(uint32_t gpio_num);
    static void setLow(uint32_t gpio_num);
    static void wait(uint32_t microseconds);
};

#endif // ESPHal_H
