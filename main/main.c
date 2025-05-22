#include "mi_led.h"
#include "esp_log.h"
#include "mi_delay.h"
#include "driver/touch_pad.h"


#define TOUCH_BUTTON_NUM 6

static const touch_pad_t buttons[TOUCH_BUTTON_NUM] = {
    TOUCH_PAD_NUM1,   // TP5 - Vol Up
    TOUCH_PAD_NUM2,   // TP2 - Play/Pause
    TOUCH_PAD_NUM3,   // TP6 - Vol Down
    TOUCH_PAD_NUM5,   // TP4 - Record
    TOUCH_PAD_NUM6,   // TP1 - Photo
    TOUCH_PAD_NUM11,  // TP3 - Network
};

void testbench_miled(void);

void app_main(void)
{
    touch_pad_init();

    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_config(buttons[i]);
    }

    // Configuración opcional de denoise
    touch_pad_denoise_t denoise = {
        .grade = TOUCH_PAD_DENOISE_BIT4,
        .cap_level = TOUCH_PAD_DENOISE_CAP_L4,
    };
    touch_pad_denoise_set_config(&denoise);
    touch_pad_denoise_enable();

    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER);
    touch_pad_fsm_start();

    printf("Iniciando lectura de botones táctiles:\n");

    while (1) {
        uint32_t value;
        for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
            touch_pad_read_raw_data(buttons[i], &value);
            printf("T%d: [%4"PRIu32"] ", buttons[i], value);
        }
        printf("\n");

        // Espera sin usar FreeRTOS
        delay(50,'m'); 
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