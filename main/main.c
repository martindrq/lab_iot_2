#include "mi_led.h"
#include "esp_log.h"
#include "mi_delay.h"
#include "mi_touch.h"
#include "driver/touch_pad.h"

led_strip_t *strip;
int STATE;


void app_main(void)
{   
    //Iniciamos el led
    led_rgb_init(&strip);
    //Iniciamos colores y brillo para el led
    float brightness = 1.0;
    int R = 255, G = 255, B = 255;
    static int color_step = 0;

    //Iniciamos el touchpad
    touch_buttons_init();

    while (1){
        delay(50,'m');
        STATE = touch_buttons_get_pressed();
        switch (STATE){
            case -1: //No se presiona nada
                
                break;
            case 0: //VOL_UP
                if (brightness < 1.0){
                    brightness += 0.1;
                    set_led_brightness(strip, R, G, B, brightness);
                }
                break;
            case 1: //PLAY/PAUSE
                R = 0;
                G = 255;
                B = 0;
                set_led_brightness(strip, R, G, B, brightness);
            break;
            case 2: //VOL_DOWN
                if (brightness > 0.0){
                    brightness -= 0.1;
                    set_led_brightness(strip, R, G, B, brightness);
                }
                break;
            case 3: //RECORD
                R = 0;
                G = 0;
                B = 255;
                set_led_brightness(strip, R, G, B, brightness);
                break;
            case 4: //PHOTO
                R = 255;
                G = 0;
                B = 0;
                set_led_brightness(strip, R, G, B, brightness);
                break;
            case 5: //NETWORK
                turn_led_off(strip);
                break;
            default:
                break;
        }
    }
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