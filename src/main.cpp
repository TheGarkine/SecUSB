
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

//#include "pio_usb.h"
#include "tusb.h"

#define LED_R 18
#define LED_G 16
#define LED_B 17 

void core1_main() {
    sleep_ms(10); 

    tusb_init();
    while (true) {
        tuh_task();
    }
}

void set_rgb(bool r, bool g, bool b) {
    gpio_put(LED_R, r);
    gpio_put(LED_G, g);
    gpio_put(LED_B, b);
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    printf("tuh_hid_report_received_cb \n");
    (void)dev_addr;
    (void)instance;
    (void)report;
    (void)len;
    set_rgb(true, false, false);
}

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    printf("tuh_hid_mount_cb \n");
    (void)dev_addr;
    (void)instance;
    (void)desc_report;
    (void)desc_len;
    set_rgb(true, false, false);
}

void tuh_msc_mount_cb(uint8_t dev_addr) {
    printf("tuh_msc_mount_cb \n");
    (void)dev_addr;
    set_rgb(false, false, true);
}

int main() {
    // default 125MHz is not appropriate. Sysclock should be multiple of 12MHz.
    set_sys_clock_khz(120000, true);

    stdio_init_all();

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);

    // for a start we want to indicate that everything is okay
    set_rgb(false, true, false);


    multicore_reset_core1();
    // all USB task run in core1
    multicore_launch_core1(core1_main);

    // The magic now works on core1, we could use this core later
    while (true) {
        tight_loop_contents();
    }
}