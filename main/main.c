#include "mi_led.h"
#include "mi_delay.h"
#include "mi_touch.h"
#include "mi_wifi_ap.h"
#include "mi_web_server.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN";

// Función callback para controlar el LED RGB desde la web
void led_control_callback(int red, int green, int blue)
{
    ESP_LOGI(TAG, "Cambiando LED a R:%d, G:%d, B:%d", red, green, blue);
    
    // Usar las funciones de tu librería mi_led.h para controlar el LED
    // Asumiendo que tienes una función para establecer colores RGB
    // Ajusta estas llamadas según las funciones disponibles en mi_led.h
    
    if (red > 0 && green == 0 && blue == 0) {
        // LED Rojo
        ESP_LOGI(TAG, "LED: ROJO");
        // Aquí llamarías a tu función para LED rojo, por ejemplo:
        // set_led_red(); 
        // O si tienes función RGB: set_led_rgb(255, 0, 0);
    } 
    else if (red == 0 && green > 0 && blue == 0) {
        // LED Verde
        ESP_LOGI(TAG, "LED: VERDE");
        // set_led_green();
        // O: set_led_rgb(0, 255, 0);
    } 
    else if (red == 0 && green == 0 && blue > 0) {
        // LED Azul
        ESP_LOGI(TAG, "LED: AZUL");
        // set_led_blue();
        // O: set_led_rgb(0, 0, 255);
    } 
    else if (red > 0 && green > 0 && blue == 0) {
        // LED Amarillo (Rojo + Verde)
        ESP_LOGI(TAG, "LED: AMARILLO");
        // set_led_yellow();
        // O: set_led_rgb(255, 255, 0);
    } 
    else if (red == 0 && green == 0 && blue == 0) {
        // LED Apagado
        ESP_LOGI(TAG, "LED: APAGADO");
        // set_led_off();
        // O: set_led_rgb(0, 0, 0);
    }
    
    // Si tu librería mi_led.h tiene una función directa para RGB, usa:
    // set_led_rgb(red, green, blue);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Iniciando aplicación ESP32 Web Server");
    
    // Inicializar el sistema de LEDs
    // Asumiendo que tienes una función de inicialización en mi_led.h
    // init_led(); // Descomenta si existe esta función
    
    // Opción 1: Crear Access Point
    ESP_LOGI(TAG, "Configurando WiFi en modo Access Point");
    init_wifi_ap("ESP32-WebServer", "12345678");
    
    // Opción 2: Conectar a red existente (comenta la línea anterior y descomenta estas)
    // ESP_LOGI(TAG, "Conectando a red WiFi existente");
    // connect_wifi_ap("NombreDeRed", "ContraseñaDeRed");
    
    // Esperar un momento para que se establezca la conexión WiFi
    vTaskDelay(pdMS_TO_TICKS(3000));
    
    // Iniciar servidor web con el callback del LED
    httpd_handle_t server = init_web_server(led_control_callback);
    
    if (server != NULL) {
        ESP_LOGI(TAG, "===========================================");
        ESP_LOGI(TAG, "Servidor web iniciado correctamente");
        ESP_LOGI(TAG, "Conéctate a la red WiFi: ESP32-WebServer");
        ESP_LOGI(TAG, "Contraseña: 12345678");
        ESP_LOGI(TAG, "Luego abre http://192.168.4.1 en tu navegador");
        ESP_LOGI(TAG, "Funcionalidades disponibles:");
        ESP_LOGI(TAG, "- Página principal: http://192.168.4.1/");
        ESP_LOGI(TAG, "- Control LED: Botones en la página web");
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