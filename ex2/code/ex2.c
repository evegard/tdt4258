/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include "ex2.h"

volatile avr32_pio_t *piob = &AVR32_PIOB;


int main (int argc, char *argv[]) {
  initHardware();

  while(1);
  return 0;
}

/* funksjon for å initialisere maskinvaren, må utvides */
void initHardware (void) {
  initIntc();
  initLeds();
  initButtons();
  initAudio();
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

int led_setup = 0;
volatile avr32_pio_t *led_pio = &AVR32_PIOC;

void set_led(int i, int on)
{
    on &= 1;
    led_setup &= ~(1 << i);
    led_setup |= (on << i);

    led_pio->codr |= 0xff;
    led_pio->sodr = led_setup;
}

int get_led(int i)
{
    return (led_setup & (1 << i)) != 0;
}

void initLeds(void)
{
    led_pio->per |= 0xff;
    led_pio->oer |= 0xff;

    set_led(0, 1);
}

void initAudio(void) {
  register_interrupt( abdac_isr, AVR32_ABDAC_IRQ/32, AVR32_ABDAC_IRQ % 32, ABDAC_INT_LEVEL);
  /* (...) */
}

void button_isr(void)
{
    volatile avr32_pio_t *pio = &AVR32_PIOB;
    int isr = pio->isr,
        pdsr = pio->pdsr;
    int i, j;
    volatile int k = 0;
    while (k < 1000) k++;
    for (i = 0; i < 8; i++) {
        if ((isr & (1 << i)) && (~pdsr & (1 << i))) {
            if (i == 0) {
                for (j = 1; j < 8; j++) {
                    if (get_led(j)) {
                        set_led(j, 0);
                        set_led(j-1, 1);
                        return;
                    }
                }
            } else if (i == 2) {
                for (j = 0; j < 7; j++) {
                    if (get_led(j)) {
                        set_led(j, 0);
                        set_led(j+1, 1);
                        return;
                    }
                }
            }
        }
    }
}

void abdac_isr(void) {}
