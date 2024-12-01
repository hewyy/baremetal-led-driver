#include <stdint.h>
#include "ESPHal.h"


void setup() {
    ESPHal::configureOutput(15);
    ESPHal::setLow(15);
    for (volatile int i = 0; i < 100; i++); // Simple delay

    while (1) {
        ESPHal::setHigh(15);
        ESPHal::wait(100);
        ESPHal::setLow(15);
        ESPHal::wait(100);
    }
}

void loop() {
}
