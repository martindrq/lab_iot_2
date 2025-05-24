#include "led_strip.h"
#include "mi_delay.h"


void turn_led_on(led_strip_t *strip, int a, int b, int c){
    strip->set_pixel(strip, 0, a, b, c);
    strip->refresh(strip, 100);
}
void turn_led_off(led_strip_t *strip){
    strip->clear(strip, 100);
}
void set_led_brightness(led_strip_t *strip, int base_r, int base_g, int base_b, float brightness) {
    //--> El brillo es un numero flotante entre 0 y 1 que multiplica al 255 de RGB
    if (brightness > 1.0){
    brightness = 1.0;
    }
    if (brightness < 0.0){
     brightness = 0.0;
    }
    //--> Multiplicamos el color que ya estaba por el factor de escalado de brillo
    int r = (int)(base_r * brightness);
    int g = (int)(base_g * brightness);
    int b = (int)(base_b * brightness);

    //--> Prendemos el LED con el nuevo brillo
    turn_led_on(strip, r, g, b);
}

void testbench_miled(void){
    //--> a, b ,c son los numeros para RGB
    int a = 255;
    int b = 255;
    int c = 255;
    led_strip_t *strip;
    led_rgb_init(&strip);
    //--> Hacemos parpadear el led infinitamente con funciones propias
    while(1){
        turn_led_on(strip, a, b, c);
        delay(500,'m');
        turn_led_off(strip);
        delay(500,'m');
    }
}