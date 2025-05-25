#include "esp_netif.h"


/**
 * @brief Inicializa el dispositivo en modo Access Point (AP).
 *
 * Esta función configura la interfaz de red WiFi del ESP32 para que funcione como un punto de acceso (Access Point),
 * permitiendo que otros dispositivos se conecten a él. Se debe proporcionar un SSID y una contraseña para definir
 * el nombre y la clave de la red WiFi que se creará.
 *
 * @param ssid Nombre (SSID) de la red WiFi que será visible para los dispositivos que se quieran conectar.
 * @param password Contraseña que los dispositivos deberán ingresar para conectarse al Access Point.
 */
void init_wifi_ap(char *ssid, char *password);

/**
 * @brief Conecta el dispositivo a una red WiFi como cliente (Station).
 *
 * Esta función configura el ESP32 para que se conecte a una red WiFi existente utilizando el SSID y la contraseña
 * proporcionados. 
 *
 * @param ssid Nombre (SSID) de la red WiFi a la que se desea conectar.
 * @param password Contraseña de la red WiFi a la que se desea conectar.
 */
void connect_wifi_ap(char *ssid, char *password);