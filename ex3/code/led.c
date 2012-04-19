#include "ap7000.h"
#include "led.h"

int led_setup = 0;
volatile avr32_pio_t *led_pio = &AVR32_PIOB;

void led_init(void)
{
    led_pio->per |= 0xffffff00;
    led_pio->oer |= 0xffffff00;
}

void led_update(void)
{
    led_pio->codr = 0xffffff00;
    led_pio->sodr = led_setup << 8;
}

void led_set_all(int new_setup)
{
    int i, j;

    led_setup = 0;

    for (i = 0; i < 8; i++) {
        if ((new_setup & (1 << i)) == 0)
            continue;
        j = i;
        switch (i) {
            case 3:
            case 4:
            case 5:
            case 6: j += 2; break;
            case 7: j = 22; break;
        }
        led_setup |= (1 << j);
    }

    led_update();
}
