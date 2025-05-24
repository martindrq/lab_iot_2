void touch_buttons_init(void);

int touch_buttons_get_pressed(void);
//--> Esta funcion usa un delay bloqueante de 10ms!
//--> Indice de los botones:
//    0 = VOL_UP
//    1 = PLAY/PAUSE
//    2 = VOL_DOWN
//    3 = RECORD
//    4 = PHOTO
//    5 = NETWORK

void buttons_for_led(void);
//--> Esta funcion usa un delay bloqueante de 50ms y es un loop infinito!