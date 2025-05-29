#ifndef MI_WEB_SERVER_H
#define MI_WEB_SERVER_H

#include "esp_http_server.h"

// Callback para controlar el LED
typedef void (*led_control_callback_t)(int red, int green, int blue);

/**
 * @brief Inicializa el servidor web HTTP
 * @param led_callback Función callback para controlar el LED RGB
 */
httpd_handle_t init_web_server(led_control_callback_t led_callback);

/**
 * @brief Detiene el servidor web HTTP
 */
void stop_web_server(httpd_handle_t server);

#endif // MI_WEB_SERVER_H