#include "mi_web_server.h"
#include "led_strip.h"  // Cambio: usar led_strip en lugar de mi_led.h
#include "esp_log.h"
#include "esp_http_server.h"
#include <string.h>

static const char *TAG = "WEB_SERVER";
static led_strip_t *g_led_strip = NULL;  // Variable global para el LED strip

// HTML embebido con botones para controlar el LED
static const char* hello_html = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
        "<title>ESP32 Web Server</title>"
        "<meta charset='UTF-8'>"
        "<style>"
            "body { font-family: Arial, sans-serif; margin: 40px; }"
            "h1 { color: #2E86AB; }"
            ".container { max-width: 600px; margin: 0 auto; }"
            ".info { background-color: #f0f8ff; padding: 20px; border-radius: 5px; margin-bottom: 20px; }"
            ".control-panel { background-color: #f9f9f9; padding: 20px; border-radius: 5px; text-align: center; }"
            ".led-button {"
                "padding: 15px 30px;"
                "margin: 10px;"
                "border: none;"
                "border-radius: 5px;"
                "font-size: 16px;"
                "font-weight: bold;"
                "cursor: pointer;"
                "color: white;"
                "text-shadow: 1px 1px 2px rgba(0,0,0,0.3);"
                "transition: transform 0.1s;"
            "}"
            ".led-button:hover { transform: scale(1.05); }"
            ".led-button:active { transform: scale(0.95); }"
            ".btn-red { background-color: #dc3545; }"
            ".btn-green { background-color: #28a745; }"
            ".btn-blue { background-color: #007bff; }"
            ".btn-yellow { background-color: #ffc107; color: black; }"
            ".btn-off { background-color: #6c757d; }"
        "</style>"
        "<script>"
            "function controlLed(color) {"
                "fetch('/led?color=' + color)"
                ".then(response => response.text())"
                ".then(data => {"
                    "console.log('LED cambiado a: ' + color);"
                    "document.getElementById('status').innerHTML = 'LED: ' + color.toUpperCase();"
                "})"
                ".catch(error => {"
                    "console.error('Error:', error);"
                    "document.getElementById('status').innerHTML = 'Error al cambiar LED';"
                "});"
            "}"
        "</script>"
    "</head>"
    "<body>"
        "<div class='container'>"
            "<h1>¡Hola Mundo!</h1>"
            "<div class='info'>"
                "<p>Bienvenido al servidor web del ESP32 del grupo de:<br><b>Nicolás Raposo, Martin Da Rosa y Rafael Durán</b></p>"
                "<p>Este mensaje se muestra desde el microcontrolador</p>"
                "<p>Servidor funcionando correctamente ✓</p>"
            "</div>"
            "<div class='control-panel'>"
                "<h2>Control del LED Strip RGB</h2>"
                "<p id='status'>LED: APAGADO</p>"
                "<div>"
                    "<button class='led-button btn-red' onclick='controlLed(\"red\")'>ROJO</button>"
                    "<button class='led-button btn-green' onclick='controlLed(\"green\")'>VERDE</button>"
                    "<button class='led-button btn-blue' onclick='controlLed(\"blue\")'>AZUL</button>"
                    "<button class='led-button btn-yellow' onclick='controlLed(\"yellow\")'>AMARILLO</button>"
                    "<button class='led-button btn-off' onclick='controlLed(\"off\")'>APAGAR</button>"
                "</div>"
            "</div>"
        "</div>"
    "</body>"
    "</html>";

// Manejador para la ruta "/"
static esp_err_t hello_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Solicitud recibida para URI: %s", req->uri);
    
    // Establecer el tipo de contenido
    httpd_resp_set_type(req, "text/html");
    
    // Enviar la respuesta HTML
    httpd_resp_send(req, hello_html, strlen(hello_html));
    
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