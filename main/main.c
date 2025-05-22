#include "mi_led.h"
#include "esp_log.h"
#include "mi_delay.h"

void testbench_miled(void);

void app_main(void)
{
    testbench_miled(); //Esto se puede borrar

}

void testbench_miled(void){
    // a, b ,c son los numeros para RGB
    int a = 255;
    int b = 255;
    int c = 255;
    led_strip_t *strip;
    led_rgb_init(&strip);
    // Hacemos parpadear el led infinitamente con funciones propias
    while(1){
        turn_led_on(strip, a, b, c);
        delay(500,'m');
        turn_led_off(strip);
        delay(500,'m');
    }
}