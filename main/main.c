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
    
    // Esperar un momento para que se establezca la conexión WiFi usando tu función delay
    delay(3000, 'm'); // 3000 milisegundos = 3 segundos
    
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
    
    // Opcional: Inicializar botones touch para control adicional
    ESP_LOGI(TAG, "Inicializando botones touch");
    touch_buttons_init();
    
    // Loop principal sin FreeRTOS
    ESP_LOGI(TAG, "Entrando en loop principal...");
    int touch_state;
    uint32_t loop_count = 0;
    
    while (1) {
        // Incrementar contador de loop
        loop_count++;
        
        // Log cada 30 segundos aproximadamente (30 iteraciones de 1 segundo)
        if (loop_count % 30 == 0) {
            ESP_LOGI(TAG, "Sistema funcionando - Loop #%lu", loop_count);
        }
        
        // Leer estado de botones touch (opcional)
        touch_state = touch_buttons_get_pressed();
        if (touch_state != -1) {
            ESP_LOGI(TAG, "Botón touch presionado: %d", touch_state);
            
            // Ejemplo de control de LED por touch (opcional)
            switch (touch_state) {
                case 0: // VOL_UP -> LED blanco brillante
                    turn_led_on(led_strip, 255, 255, 255);
                    ESP_LOGI(TAG, "LED encendido - Blanco");
                    break;
                case 1: // PLAY/PAUSE -> LED verde
                    turn_led_on(led_strip, 0, 255, 0);
                    ESP_LOGI(TAG, "LED encendido - Verde");
                    break;
                case 2: // VOL_DOWN -> LED con brillo reducido
                    set_led_brightness(led_strip, 255, 255, 255, 0.3);
                    ESP_LOGI(TAG, "LED encendido - Brillo reducido");
                    break;
                case 3: // RECORD -> LED azul
                    turn_led_on(led_strip, 0, 0, 255);
                    ESP_LOGI(TAG, "LED encendido - Azul");
                    break;
                case 4: // PHOTO -> LED rojo
                    turn_led_on(led_strip, 255, 0, 0);
                    ESP_LOGI(TAG, "LED encendido - Rojo");
                    break;
                case 5: // NETWORK -> Apagar LED
                    turn_led_off(led_strip);
                    ESP_LOGI(TAG, "LED apagado");
                    break;
                default:
                    break;
            }
        }
        // Delay de 1 segundo usando tu función delay personalizada
        delay(1000, 'm'); // 1000 milisegundos = 1 segundo
    }
}