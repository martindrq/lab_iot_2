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

## Segunda Parte: Crear Access Point y conectar a WiFi
**Descripción General**<br />
Esta parte del laboratorio implementa un Access Point (AP) que permite a los usuarios conectarse a la red WiFi creada por el ESP32.
Tambien se proporciona otro metodo capaz de conectarse a una red WiFi existente.<br /><br />
**Instrucciones de Uso**<br />
Incluír la librería:<br />
```c
#include "mi_wifi_ap.h"
```
Iniciar el Access Point:<br />
```c
init_wifi_ap("ESP32-WebServer", "12345678");
```
Eventos útiles asociados al AP:<br />
- WIFI_EVENT_AP_START: Se emite cuando el AP se inicia correctamente.
- WIFI_EVENT_AP_STACONNECTED: Se emite cuando un cliente se conecta al AP.
- WIFI_EVENT_AP_STADISCONNECTED: Se emite cuando un cliente se desconecta del AP.
Conectar a una Red WiFi Existente<br />
```c
connect_wifi_ap("NombreDeRed", "ContraseñaDeRed");
```
Eventos útiles asociados al STA:<br />
- WIFI_EVENT_STA_START: Se emite cuando el ESP32 comienza a buscar redes WiFi.
- WIFI_EVENT_STA_CONNECTED: Se emite cuando el ESP32 se conecta a la red WiFi.
- WIFI_EVENT_STA_DISCONNECTED: Se emite cuando el ESP32 pierde la conexión a la red WiFi.

## Tercera Parte: Servidor Web con Control de LED Strip
**Descripción General**<br />
Esta parte implementa un servidor web que permite controlar el LED de la placa a través de una interfaz web.

Instrucciones de Uso<br />
1. Compilar y Flashear el Código<br />
bashidf.py build<br />
idf.py flash monitor<br />
2. Conectar a la Red WiFi<br />

Red: ESP32-WebServer<br />
Contraseña: 12345678<br />

3. Acceder a la Interfaz Web<br />

Abrir navegador en: http://192.168.4.1<br />

**API Endpoints**<br />

GET/Página principal con interfaz de control<br />
POST/led/colorCambiar color del LED<br />
POST/led/effectAplicar efectos especiales<br />
POST/led/powerEncender/apagar LED<br />

**Configuración WiFi Alternativa** <br />

Para conectar a una red existente en lugar de crear un Access Point, modificar en main.c:<br />
Comentar esta línea:<br />
// init_wifi_ap("ESP32-WebServer", "12345678");<br />

// Descomentar y configurar:<br />
connect_wifi_ap("NombreDeRed", "ContraseñaDeRed");<br />