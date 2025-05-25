idf_component_register(
    SRCS "mi_wifi_ap.c" 
    INCLUDE_DIRS "include" 
    PRIV_REQUIRES "led_strip" 
    PRIV_REQUIRES "mi_delay" 
    PRIV_REQUIRES "nvs_flash"
    PRIV_REQUIRES "esp_netif"
    PRIV_REQUIRES "esp_wifi" 
    PRIV_REQUIRES "esp_event")