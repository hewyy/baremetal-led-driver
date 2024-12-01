#include "ESPHal.h"

#define DR_REG_GPIO_BASE    0x3FF44000
#define DR_REG_IO_MUX_BASE  0x3FF49000

#define GPIO_ENABLE_W1TS_REG        (DR_REG_GPIO_BASE + 0x24)
#define GPIO_ENABLE_W1TC_REG        (DR_REG_GPIO_BASE + 0x28) 
#define GPIO_FUNC_OUT_SEL_CFG_REG   (DR_REG_GPIO_BASE + 0x530)
#define GPIO_ENABLE_REG             (DR_REG_GPIO_BASE + 0x20)

#define GPIO_OUT_SET_REG            (DR_REG_GPIO_BASE + 0x0008)
#define GPIO_OUT_CLEAR_REG          (DR_REG_GPIO_BASE + 0x000c)

#define CPU_CLOCK_HZ 240000000UL  // Replace with your microcontroller's clock speed if different


void ESPHal::configureOutput(uint32_t gpio_num) {
    // TODO: implement for more pins
    // issues with the documented address offset for IO_MUX_x_REG in ESPs reference manual (page 78)
    if (gpio_num != 15) {
        return;
    }

    *(volatile uint32_t*)GPIO_ENABLE_REG = 0x8F80;

    volatile uint32_t* gpio_func_out_sec_address = (volatile uint32_t*)GPIO_FUNC_OUT_SEL_CFG_REG + gpio_num * 4;
    *gpio_func_out_sec_address = 0x100;

    volatile uint32_t* io_mux_reg_base = (volatile uint32_t*)0x3FF4903C;
    *io_mux_reg_base = 0x2B00;
}

void ESPHal::setHigh(uint32_t gpio_num) {
    *(volatile uint32_t *)GPIO_OUT_SET_REG = 1 << gpio_num;
}

void ESPHal::setLow(uint32_t gpio_num) {
    *(volatile uint32_t *)GPIO_OUT_CLEAR_REG = 1 << gpio_num;
}

void ESPHal::wait(uint32_t microseconds) {
    // number of CPU cycles needed to wait
    uint32_t cycles_per_iteration = 7; // Estimate loop overhead (e.g., increment, compare, branch)
    uint32_t cycles = ((CPU_CLOCK_HZ / 1000000) * microseconds) / cycles_per_iteration;

    for (uint32_t i=0; i<cycles; i++) {
        __asm__ volatile ("nop\n\t" :::);
    }
}
