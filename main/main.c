#include "mi_led.h"
#include "esp_log.h"
#include "mi_delay.h"
#include "mi_touch.h"
#include "driver/touch_pad.h"

void get_state();
#define TOUCH_THRESHOLD 19000
#define TOUCH_BUTTON_NUM 6
int button_pressed;
char STATE;
led_strip_t *strip;

static const touch_pad_t buttons[TOUCH_BUTTON_NUM] = {
    TOUCH_PAD_NUM1,   // TP5 - VOL_UP
    TOUCH_PAD_NUM2,   // TP2 - PLAY/PAUSE
    TOUCH_PAD_NUM3,   // TP6 - VOL_DOWN
    TOUCH_PAD_NUM5,   // TP4 - RECORD
    TOUCH_PAD_NUM6,   // TP1 - PHOTO
    TOUCH_PAD_NUM11,  // TP3 - NETWORK
};

void app_main(void)
{   
    //Iniciamos el led
    led_rgb_init(&strip);

    // Iniciamos el touchpad
    touch_pad_init(); 
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        // Configuramos todos los botones
        touch_pad_config(buttons[i]);
    }
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_SW);

    while(1){
        get_state();
        
        switch (STATE)
        {
            case 'A':
                turn_led_on(strip, 255, 0, 0);
                break;
            case 'B':
                turn_led_off(strip);
                break;
            case 'X':
                turn_led_on(strip, 255, 255, 255);
                break;
            default:
                turn_led_off(strip);
                break;
        }
        
    }
}

void get_state(void){

    uint32_t value;

    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_sw_start();
        delay(10,'m');
        touch_pad_read_raw_data(buttons[i], &value);
        printf("T%d: [%4"PRIu32"]\n", buttons[i], value);
            if (value > TOUCH_THRESHOLD){
              button_pressed = i;
              switch (button_pressed)
              {
                case 0:
                    STATE = 'A';
                    printf("Boton VOL_UP presionado, STATE A\n");
                    
                    return;
                case 2:
                    STATE = 'B';
                    printf("Boton VOL_DOWN presionado, STATE B\n");
                    return;
                default:
                    STATE = 'X';
                    printf("Boton %d presionado, parece no hacer nada\n", button_pressed);
                    return;
            }
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