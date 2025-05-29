idf_component_register(SRCS "main.c"
                      INCLUDE_DIRS "."
                      REQUIRES mi_web_server mi_wifi_ap mi_led mi_delay mi_touch)