idf_component_register(SRCS "mi_touch.c"
                    INCLUDE_DIRS "include"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES mi_led mi_delay led_strip driver)