#include "led_strip.h"

void blink_led(led_strip_t *strip);

void one_blink(led_strip_t *strip);

void turn_led_on(led_strip_t *strip, int a, int b, int c);

void turn_led_off(led_strip_t *strip);

void set_led_brightness(led_strip_t *strip, int base_r, int base_g, int base_b, float brightness);