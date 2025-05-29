idf_component_register(
    SRCS "mi_wifi_ap.c" 
    INCLUDE_DIRS "include" 
    REQUIRES led_strip mi_delay nvs_flash esp_netif esp_wifi esp_event)
