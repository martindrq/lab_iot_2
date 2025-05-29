#ifndef MI_WEB_SERVER_H
#define MI_WEB_SERVER_H

#include "esp_http_server.h"
#include "led_strip.h"

/**
 * @brief Inicializa el servidor web HTTP
 * @param led_strip Puntero al LED strip configurado
 */
httpd_handle_t init_web_server(led_strip_t *led_strip);

/**
 * @brief Detiene el servidor web HTTP
 */
void stop_web_server(httpd_handle_t server);

void init_web_services();

#endif // MI_WEB_SERVER_H