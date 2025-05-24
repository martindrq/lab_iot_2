#include "led_strip.h"
#include "mi_delay.h"


void blink_led(led_strip_t *strip)
{
        strip->set_pixel(strip, 0, 255, 0, 0);
        strip->refresh(strip, 100);
        delay(500,'m');

        strip->clear(strip, 100);
        delay(500,'m');
        
        strip->set_pixel(strip, 0, 0, 255, 0);
        strip->refresh(strip, 100);
        delay(500,'m');

        strip->clear(strip, 100);
        delay(500,'m');

        strip->set_pixel(strip, 0, 0, 0, 255);
        strip->refresh(strip, 100);
        delay(500,'m');

        strip->clear(strip, 100);
        delay(500,'m');
}
void one_blink(led_strip_t *strip){

    strip->set_pixel(strip, 0, 255, 0, 0);
    strip->refresh(strip, 100);
    delay(250,'m');
    strip->clear(strip, 100);
    delay(250,'m');

}
void turn_led_on(led_strip_t *strip, int a, int b, int c){
    strip->set_pixel(strip, 0, a, b, c);
    strip->refresh(strip, 100);
}
void turn_led_off(led_strip_t *strip){
    strip->clear(strip, 100);
}
void set_led_brightness(led_strip_t *strip, int base_r, int base_g, int base_b, float brightness) {
    if (brightness > 1.0){
    brightness = 1.0;
    }
    if (brightness < 0.0){
     brightness = 0.0;
    }
    int r = (int)(base_r * brightness);
    int g = (int)(base_g * brightness);
    int b = (int)(base_b * brightness);

    turn_led_on(strip, r, g, b);
}