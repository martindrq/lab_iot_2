## Laboratorio 2 - Control de LED y Servidor Web

**Integrantes:** Nicolas Raposo, Martin Da Rosa y Rafael Durán.

**Configuración Inicial**
Es posible que sea necesario modificar los archivos de la carpeta .vscode para actualizar los paths si la extensión está instalada en una ubicación diferente al default.

## Primera Parte: Laboratorio_2a

**Descripción:**<br />
Para la primera parte, cargar en la placa el código de la rama Laboratorio_2a. La función buttons_for_led() contiene el loop infinito para usar los botones del touchpad y cambiar el estado del LED.
Funcionalidad de Botones
Para la primera parte hay que cargar en la placa el código de la rama Laboratorio_2a, la funcion buttons_for_led() tiene el loop infinito para usar los botones del touchpad y cambiar el estado del LED, los botones hacen lo siguiente:

VOL_UP -> Sube brillo     (hay que mantener presionado)<br />
VOL_DOWN -> Baja brillo   (hay que mantener presionado)<br />
PHOTO -> Color rojo       (funciona con 1 toque)<br />
PLAY/PAUSE -> Color verde (funciona con 1 toque)<br />
RECORD -> Color azul      (funciona con 1 toque)<br />
NETWORK -> Apaga el LED   (funciona con 1 toque)<br />


## Tercera Parte: Servidor Web con Control de LED Strip
**Descripción General**<br />
Esta parte implementa un servidor web que permite controlar un LED strip WS2812 a través de una interfaz web.

**Características Principales**<br />

**Servidor Web HTTP:** Crea un Access Point WiFi con credenciales predefinidas<br />
**Control de LED Strip:** Interfaz web para controlar colores y efectos del LED strip<br />
**API REST:** Endpoints para control programático del LED<br />
**Compatibilidad:** Funciona con LED strips WS2812/NeoPixel<br />

**Configuración de Hardware**<br />

**LED Strip:** Conectado al pin GPIO_NUM_45 (configurado por defecto en la placa Kaluga)<br />
WiFi: Modo Access Point habilitado<br />

Instrucciones de Uso<br />
1. Compilar y Flashear el Código<br />
bashidf.py build<br />
idf.py flash monitor<br />
2. Conectar a la Red WiFi<br />

Red: ESP32-WebServer<br />
Contraseña: 12345678<br />

3. Acceder a la Interfaz Web<br />

Abrir navegador en: http://192.168.4.1<br />

4. Funcionalidades Disponibles<br />

Control de colores individuales (RGB)<br />
Efectos predefinidos<br />
Encendido/apagado del LED strip<br />
Ajuste de brillo<br />

Estructura del Proyecto<br />
components/<br />
├── led_strip/          # Driver personalizado para WS2812<br />
├── mi_web_server/      # Servidor HTTP con endpoints<br />
├── mi_wifi_ap/         # Configuración WiFi Access Point<br />
├── mi_led/             # Funciones auxiliares LED<br />
├── mi_delay/           # Utilidades de delay<br />
└── mi_touch/           # Driver touchpad<br />

**API Endpoints**<br />

GET/Página principal con interfaz de control<br />
POST/led/colorCambiar color del LED<br />
POST/led/effectAplicar efectos especiales<br />
POST/led/powerEncender/apagar LED<br />

**Configuración WiFi Alternativa** <br />

Para conectar a una red existente en lugar de crear un Access Point, modificar en main.c:<br />
c// Comentar esta línea:<br />
// init_wifi_ap("ESP32-WebServer", "12345678");<br />

// Descomentar y configurar:<br />
connect_wifi_ap("NombreDeRed", "ContraseñaDeRed");<br />

**Especificaciones Técnicas**<br />

Utiliza driver RMT para comunicación con LED strip WS2812<br />
Implementación compatible con ESP-IDF v5.4.1<br />
Optimizado para ESP32-S2 (placa Kaluga)<br />
Manejo de errores y logging detallado<br />

**Troubleshooting**<br />
Si hay problemas de compilación, verificar:<br />

Dependencias: Revisar CMakeLists.txt de cada componente<br />
Versión ESP-IDF: Se recomienda v5.4.1<br />
Configuración de pines: Verificar según la placa utilizada<br />

**Recursos Adicionales** <br />

Documentación ESP-IDF<br />
Especificaciones WS2812<br />
ESP32-S2 Kaluga Kit<br />
