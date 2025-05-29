#include "mi_led.h"
#include "mi_delay.h"
#include "mi_touch.h"
#include "mi_wifi_ap.h"
#include "mi_web_server.h"
#include "led_strip.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    //Función para la parte 1:
    //buttons_for_leds();

    //Función para la parte 2:
    // connect_wifi_ap("SSID", "Contraseña");
   
    //Función para la parte 3:
    init_web_services();
}