#include "mi_led.h"
#include "mi_delay.h"
#include "mi_touch.h"
#include "mi_wifi_ap.h"
#include "mi_web_server.h"
#include "led_strip.h"  // Agregar include para LED strip
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando aplicación ESP32 Web Server");
    
    // Usar tu función personalizada led_rgb_init()
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
    
    // Opción 2: Conectar a red existente (comenta la línea anterior y descomenta estas)
    // ESP_LOGI(TAG, "Conectando a red WiFi existente");
    // connect_wifi_ap("NombreDeRed", "ContraseñaDeRed");
    
    // Esperar un momento para que se establezca la conexión WiFi
    vTaskDelay(pdMS_TO_TICKS(3000));
    
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
    
    // Loop principal
    while (1) {
        // Aquí puedes agregar otras tareas si es necesario
        // Por ejemplo, leer sensores touch, etc.
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}