#include "esp_rom_sys.h"

void delay(uint32_t tiempo, char unidad)
{
    switch (unidad) {
        case 'u': //--> microsegundos
            esp_rom_delay_us(tiempo);
            break;
        case 'm': //--> milisegundos
            esp_rom_delay_us(tiempo * 1000);
            break;
        case 's': //--> segundos
            esp_rom_delay_us(tiempo * 1000000);
            break;
    }
}
