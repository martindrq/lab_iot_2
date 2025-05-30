idf_component_register(SRCS "mi_web_server.c"
                      INCLUDE_DIRS "."
                      REQUIRES esp_http_server led_strip mi_wifi_ap mi_delay 
                      EMBED_FILES "index.html")