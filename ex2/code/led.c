#include <avr32/ap7000.h>

#include "led.h"

/* The current LED setup. */
int led_setup = 0;

/* Set a pointer to the location of PIOC control registers. */
volatile avr32_pio_t *led_pio = &AVR32_PIOC;

/* Initialize LED I/O. */
void led_init()
{
    /* Enable the lower eight ports. */
    led_pio->per |= 0xff;
    /* Enable output for the lower eight ports. */
    led_pio->oer |= 0xff;
}

/* Update the LEDs according to 'led_setup'. */
void led_update()
{
    /* Clear the output on the lower eight pins. */
    led_pio->codr |= 0xff;
    /* Set the output of the pins according to 'led_setup'. */
    led_pio->sodr = led_setup;
}

/* Set the value of a specific LED. */
void led_set(int i, int on)
{
    /* Mask and set the values. */
    on &= 1;
    led_setup &= ~(1 << i);
    led_setup |= (on << i);
    /* Update the data pins. */
    led_update();
}

/* Get the state of a specific LED. */
int led_get(int i)
{
    return (led_setup & (1 << i)) != 0;
}

/* Clear all LEDs. */
void led_clear()
{
    /* Clear the internal state of the LEDs. */
    led_setup = 0;
    /* Update the data pins. */
    led_update();
}
