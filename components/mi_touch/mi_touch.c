#include "esp_log.h"
#include "mi_delay.h"
#include "driver/touch_pad.h"

#define TOUCH_THRESHOLD 19000
#define TOUCH_BUTTON_NUM 6

static const touch_pad_t buttons[TOUCH_BUTTON_NUM] = {
    TOUCH_PAD_NUM1,   // TP5 - VOL_UP
    TOUCH_PAD_NUM2,   // TP2 - PLAY/PAUSE
    TOUCH_PAD_NUM3,   // TP6 - VOL_DOWN
    TOUCH_PAD_NUM5,   // TP4 - RECORD
    TOUCH_PAD_NUM6,   // TP1 - PHOTO
    TOUCH_PAD_NUM11,  // TP3 - NETWORK
};

void touch_buttons_init(void){
    // Iniciamos el touchpad
    touch_pad_init();

    // Configuramos todos los botones
    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_config(buttons[i]);
    }
    // Iniciamos el touchpad para medidas manuales con touch_pad_read_raw_data
    touch_pad_set_fsm_mode(TOUCH_FSM_MODE_SW);
}

int touch_buttons_get_pressed(void){
    uint32_t value;

    for (int i = 0; i < TOUCH_BUTTON_NUM; i++) {
        touch_pad_sw_start();
        delay(10, 'm');
        touch_pad_read_raw_data(buttons[i], &value);
        printf("T%d: [%4"PRIu32"]\n", buttons[i], value);
        if (value > TOUCH_THRESHOLD) {
            return i;
        }
    }
    return -1;
}
