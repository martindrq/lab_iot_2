#include "mi_led.h"
#include "mi_delay.h"
#include "mi_touch.h"
#include "esp_log.h"

void app_main(void)
{
    buttons_for_led(); // Esto se puede borrar, la funcion es el loop infinito
                       // para cambiar el estado del LED con el touchpad
}