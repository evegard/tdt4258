/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include <stdlib.h>
#include <math.h>

#include "ex2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;

int main (int argc, char *argv[]) {
    initHardware();

    mel_play_loop();
    return 0;
}

/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware (void) {
  initIntc();
  led_init();
  initButtons();
  snd_init();
}

void initIntc(void) {
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);
  init_interrupts();
}

void initButtons(void) {
    register_interrupt( button_isr, AVR32_PIOB_IRQ/32, AVR32_PIOB_IRQ % 32, BUTTONS_INT_LEVEL);

    volatile avr32_pio_t *pio = &AVR32_PIOB;
    pio->per |= 0xff;
    pio->puer |= 0xff;
    pio->ier |= 0xff;
}

void button_isr(void)
{
    /* Do debouncing before reading the data pins. */
    volatile int k = 1000;
    while (k--);

    volatile avr32_pio_t *pio = &AVR32_PIOB;
    int isr = pio->isr, pdsr = pio->pdsr;
    int i;
    for (i = 0; i < 8; i++)
        if ((isr & (1 << i)) && (~pdsr & (1 << i)))
            mel_set_melody(i);
}

