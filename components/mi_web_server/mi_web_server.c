#include "mi_web_server.h"
#include "led_strip.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include <string.h>
#include "mi_wifi_ap.h"
#include "mi_delay.h"

extern const uint8_t index_html_start[] asm("_binary_index_html_start");
static const char *TAG = "WEB_SERVER";
static led_strip_t *g_led_strip = NULL;  // Variable global para el LED strip


// Manejador para la ruta "/"
static esp_err_t hello_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Solicitud recibida para URI: %s", req->uri);
    
    // Establecer el tipo de contenido
    httpd_resp_set_type(req, "text/html");
    
    // Enviar la respuesta HTML
    extern const char resp[] asm("_binary_index_html_start");
    httpd_resp_send(req, resp, strlen(resp));
    
    return ESP_OK;
}

// Manejador para controlar el LED
static esp_err_t led_handler(httpd_req_t *req)
{
    char query[100];
    size_t query_len = httpd_req_get_url_query_len(req);
    
    if (query_len > 0 && query_len < sizeof(query)) {
        httpd_req_get_url_query_str(req, query, sizeof(query));
        ESP_LOGI(TAG, "Query recibida: %s", query);
        
        char color_param[20];
        if (httpd_query_key_value(query, "color", color_param, sizeof(color_param)) == ESP_OK) {
            ESP_LOGI(TAG, "Color solicitado: %s", color_param);
            
            // Controlar el LED strip según el color
            if (strcmp(color_param, "red") == 0) {
                ESP_LOGI(TAG, "LED Strip: ROJO");
                if (g_led_strip != NULL) {
                    g_led_strip->set_pixel(g_led_strip, 0, 255, 0, 0);  // R, G, B
                    g_led_strip->refresh(g_led_strip, 100);
                }
            } else if (strcmp(color_param, "green") == 0) {
                ESP_LOGI(TAG, "LED Strip: VERDE");
                if (g_led_strip != NULL) {
                    g_led_strip->set_pixel(g_led_strip, 0, 0, 255, 0);  // R, G, B
                    g_led_strip->refresh(g_led_strip, 100);
                }
            } else if (strcmp(color_param, "blue") == 0) {
                ESP_LOGI(TAG, "LED Strip: AZUL");
                if (g_led_strip != NULL) {
                    g_led_strip->set_pixel(g_led_strip, 0, 0, 0, 255);  // R, G, B
                    g_led_strip->refresh(g_led_strip, 100);
                }
            } else if (strcmp(color_param, "yellow") == 0) {
                ESP_LOGI(TAG, "LED Strip: AMARILLO");
                if (g_led_strip != NULL) {
                    g_led_strip->set_pixel(g_led_strip, 0, 255, 255, 0);  // R, G, B (Rojo + Verde = Amarillo)
                    g_led_strip->refresh(g_led_strip, 100);
                }
            } else if (strcmp(color_param, "off") == 0) {
                ESP_LOGI(TAG, "LED Strip: APAGADO");
                if (g_led_strip != NULL) {
                    g_led_strip->clear(g_led_strip, 100);
                }
            } else {
                ESP_LOGW(TAG, "Color no reconocido: %s", color_param);
            }
            
            // Responder con éxito
            httpd_resp_set_type(req, "text/plain");
            httpd_resp_send(req, "OK", 2);
        } else {
            // Error en el parámetro
            httpd_resp_set_status(req, "400 Bad Request");
            httpd_resp_send(req, "Parámetro 'color' requerido", 28);
        }
    } else {
        // Error en la query
        httpd_resp_set_status(req, "400 Bad Request");
        httpd_resp_send(req, "Query inválida", 14);
    }
    
    return ESP_OK;
}

// Configuración de las rutas
static const httpd_uri_t hello_uri = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = hello_handler,
    .user_ctx  = NULL
};

static const httpd_uri_t led_uri = {
    .uri       = "/led",
    .method    = HTTP_GET,
    .handler   = led_handler,
    .user_ctx  = NULL
};

httpd_handle_t init_web_server(led_strip_t *led_strip)
{
    g_led_strip = led_strip;  // Guardar referencia al LED strip
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    
    // Configuraciones del servidor
    config.server_port = 80;
    config.max_uri_handlers = 10;
    config.max_resp_headers = 8;
    config.max_open_sockets = 7;
    config.keep_alive_enable = true;
    config.keep_alive_idle = 5;
    config.keep_alive_interval = 5;
    config.keep_alive_count = 3;
    
    ESP_LOGI(TAG, "Iniciando servidor HTTP en puerto %d", config.server_port);
    
    // Iniciar el servidor HTTP
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Registrando manejadores de URI");
        
        // Registrar los manejadores
        httpd_register_uri_handler(server, &hello_uri);
        httpd_register_uri_handler(server, &led_uri);
        
        ESP_LOGI(TAG, "Servidor web iniciado exitosamente");
        return server;
    }
    
    ESP_LOGE(TAG, "Error al iniciar el servidor HTTP");
    return NULL;
}

void stop_web_server(httpd_handle_t server)
{
    if (server != NULL) {
        httpd_stop(server);
        ESP_LOGI(TAG, "Servidor web detenido");
    }
}

void init_web_services(){

    ESP_LOGI(TAG, "Iniciando aplicación ESP32 Web Server");
    
    led_strip_t *led_strip = NULL;
    ESP_ERROR_CHECK(led_rgb_init(&led_strip));
    
    if (!led_strip) {
        ESP_LOGE(TAG, "Error al crear el LED strip");
        return;
    }
    
    ESP_LOGI(TAG, "LED strip configurado correctamente");
    
    // Opción 1: Crear Access Point
    ESP_LOGI(TAG, "Configurando WiFi en modo Access Point");
    init_wifi_ap("ESP32-WebServer", "12345678");
    
    // Opción 2: Conectar a red existente (comentar opción 1 y descomentar estas lineas para usar)
    // ESP_LOGI(TAG, "Conectando a red WiFi existente");
    // connect_wifi_ap("NombreDeRed", "ContraseñaDeRed");
    
    // Esperar un momento para que se establezca la conexión WiFi usando tu función delay
    delay(3000, 'm');
    
    // Iniciar servidor web con el LED strip
    httpd_handle_t server = init_web_server(led_strip);
    
    if (server != NULL) {
        ESP_LOGI(TAG, "===========================================");
        ESP_LOGI(TAG, "Servidor web iniciado correctamente");
        ESP_LOGI(TAG, "Conéctate a la red WiFi: ESP32-WebServer");
        ESP_LOGI(TAG, "Contraseña: 12345678");
        ESP_LOGI(TAG, "Luego abre http://192.168.4.1 en tu navegador");
        ESP_LOGI(TAG, "Funcionalidades disponibles:");
        ESP_LOGI(TAG, "- Página principal: http://192.168.4.1/");
        ESP_LOGI(TAG, "- Control LED Strip: Botones en la página web");
        ESP_LOGI(TAG, "===========================================");
    } else {
        ESP_LOGE(TAG, "Error al iniciar el servidor web");
        return;
    }

}