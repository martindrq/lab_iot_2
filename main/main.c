#include <stdio.h>
#include "mi_led.h"
#include "esp_log.h"

void blink_led(led_strip_t *strip);

void app_main(void)
{
    led_strip_t *strip;
    led_rgb_init(&strip);
    blink_led(strip);
}