#include "led_strip.h"

void blink_led(led_strip_t *strip)
{
    while (1) {
        strip->set_pixel(strip, 0, 255, 0, 0);
        strip->refresh(strip, 100);
    }
}