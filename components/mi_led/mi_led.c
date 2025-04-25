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