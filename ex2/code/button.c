#include <avr32/ap7000.h>
#include <sys/interrupts.h>

#include "button.h"
#include "melody.h"

#define BTN_INT_LEVEL 0

/* Set a pointer to the location of PIOB control registers. */
volatile avr32_pio_t *btn_pio = &AVR32_PIOB;

/* Initialize button I/O. */
void btn_init()
{
    /* Register 'btn_interrupt' as the interrupt routine. */
    register_interrupt(
        btn_interrupt,
        AVR32_PIOB_IRQ / 32,
        AVR32_PIOB_IRQ % 32,
        BTN_INT_LEVEL);

    /* Enable the lower eight ports. */
    btn_pio->per |= 0xff;
    /* Enable pull-up resistors for the lower eight ports. */
    btn_pio->puer |= 0xff;
    /* Enable interrupts for the lower eight ports. */
    btn_pio->ier |= 0xff;
}

/* Button interrupt routine. */
void btn_interrupt()
{
    volatile int k;
    int isr, pdsr, i;

    /* A busy wait loop of 1000 cycles to avoid bouncing effects on the
     * button readings. Do this before reading the data pins. */
    k = 1000;
    while (k--);

    /* Read the Interrupt Status Register. */
    isr = btn_pio->isr;
    /* Read the button I/O pins. */
    pdsr = btn_pio->pdsr;
    /* Loop through the eight buttons. */
    for (i = 0; i < 8; i++)
        /* Check whether the current button generated the interrupt and
         * whether the button is currently pushed down. */
        if ((isr & (1 << i)) && (~pdsr & (1 << i)))
            /* Set the current melody accordingly. */
            mel_set_melody(i);
}
