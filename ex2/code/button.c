#include <avr32/ap7000.h>
#include <sys/interrupts.h>

#include "button.h"
#include "melody.h"

#define BTN_INT_LEVEL 0

volatile avr32_pio_t *btn_pio = &AVR32_PIOB;

void btn_init()
{
    register_interrupt(
        btn_interrupt,
        AVR32_PIOB_IRQ / 32,
        AVR32_PIOB_IRQ % 32,
        BTN_INT_LEVEL);

    btn_pio->per |= 0xff;
    btn_pio->puer |= 0xff;
    btn_pio->ier |= 0xff;
}

void btn_interrupt()
{
    volatile int k;
    int isr, pdsr, i;

    /* Debouncing wait loop (before reading the data pins). */
    k = 1000;
    while (k--);

    isr = btn_pio->isr;
    pdsr = btn_pio->pdsr;
    for (i = 0; i < 8; i++)
        if ((isr & (1 << i)) && (~pdsr & (1 << i)))
            mel_set_melody(i);
}
