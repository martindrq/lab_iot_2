#include "mi_led.h"
#include "esp_log.h"
#include "mi_delay.h"

void blink_led(led_strip_t *strip);

void app_main(void)
{
    led_strip_t *strip;
    led_rgb_init(&strip);
    while(1){
        blink_led(strip);
    }
}