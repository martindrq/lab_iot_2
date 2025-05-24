#include "mi_delay.h"
#include "mi_led.h"
#include "esp_log.h"
#include "driver/touch_pad.h"


#define TOUCH_THRESHOLD 19000 //--> Umbral para el valor en crudo que detecta si fue presionado
#define TOUCH_BUTTON_NUM 6 //--> Cantidad de botones

//--> Array con los botones del touchpad
static const touch_pad_t buttons[TOUCH_BUTTON_NUM] = {
    TOUCH_PAD_NUM1,   // TP5 - VOL_UP
    TOUCH_PAD_NUM2,   // TP2 - PLAY/PAUSE
    TOUCH_PAD_NUM3,   // TP6 - VOL_DOWN
    TOUCH_PAD_NUM5,   // TP4 - RECORD
    TOUCH_PAD_NUM6,   // TP1 - PHOTO
    TOUCH_PAD_NUM11,  // TP3 - NETWORK
};

void touch_buttons_init(void){
    //--> Iniciamos el touchpad
    touch_pad_init();

    //--> Configuramos todos los botones
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_config(buttons[i]);
    }
    //--> Iniciamos el touchpad para medidas manuales con touch_pad_read_raw_data
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_SW);
}

int touch_buttons_get_pressed(void){
    //--> value tiene el valor en crudo obtenido del touchpad
    uint32_t value;

    //--> Recorremos cada boton, tomamos la medida y si alguna supera el umbral la retornamos
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_sw_start(); //--> Inicia la medicion
        delay(10, 'm'); //--> Este delay le da tiempo a hacer la medida
        touch_pad_read_raw_data(buttons[i], &value); //--> Lee la medicion
        //printf("T%d: [%4"PRIu32"]\n", buttons[i], value); //--> Este print es para calibrar el THRESHOLD
        if (value > TOUCH_THRESHOLD) {
            return i;
        }
    }
    return -1;
}

void buttons_for_led(void){   
    led_strip_t *strip;
    int STATE;

    //--> Iniciamos el led
    led_rgb_init(&strip);
    
    //--> Iniciamos colores y brillo para el led
    float brightness = 1.0;
    int R = 255, G = 255, B = 255;


    //--> Iniciamos el touchpad
    touch_buttons_init();

    while (1){
        delay(50,'m');
        STATE = touch_buttons_get_pressed();
        switch (STATE){
            case -1: //No se presiona nada
                break;
            case 0: //VOL_UP -> Sube brillo
                if (brightness < 1.0){
                    brightness += 0.05;
                    set_led_brightness(strip, R, G, B, brightness);
                }
                break;
            case 1: //PLAY/PAUSE -> Color verde
                R = 0;
                G = 255;
                B = 0;
                set_led_brightness(strip, R, G, B, brightness);
            break;
            case 2: //VOL_DOWN -> Baja brillo
                if (brightness > 0.0){
                    brightness -= 0.05;
                    set_led_brightness(strip, R, G, B, brightness);
                }
                break;
            case 3: //RECORD -> Color azul
                R = 0;
                G = 0;
                B = 255;
                set_led_brightness(strip, R, G, B, brightness);
                break;
            case 4: //PHOTO -> Color rojo
                R = 255;
                G = 0;
                B = 0;
                set_led_brightness(strip, R, G, B, brightness);
                break;
            case 5: //NETWORK -> Apaga el LED
                turn_led_off(strip);
                break;
            default:
                break;
        }
    }
}
