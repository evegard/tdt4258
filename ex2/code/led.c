#include <avr32/ap7000.h>

#include "led.h"

int led_setup = 0;
volatile avr32_pio_t *led_pio = &AVR32_PIOC;

void led_init()
{
    led_pio->per |= 0xff;
    led_pio->oer |= 0xff;
}

void led_update()
{
    led_pio->codr |= 0xff;
    led_pio->sodr = led_setup;
}

void led_set(int i, int on)
{
    on &= 1;
    led_setup &= ~(1 << i);
    led_setup |= (on << i);
    led_update();
}

int led_get(int i)
{
    return (led_setup & (1 << i)) != 0;
}

void led_clear()
{
    led_setup = 0;
    led_update();
}
