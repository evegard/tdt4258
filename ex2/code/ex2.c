/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include <stdlib.h>
#include <math.h>

#include "ex2.h"

static double *notes;

void initNotes()
{
    int note_count = 12, i;
    notes = malloc(note_count * sizeof(double));
    for (i = 0; i < note_count; i++) {
        notes[i] = 440 * pow(2, (i - 9) / 12.0);
    }
}

#define C       0
#define C_SHARP 1
#define D       2
#define D_SHARP 3
#define E       4
#define F       5
#define F_SHARP 6
#define G       7
#define G_SHARP 8
#define A       9
#define A_SHARP 10
#define B       11

volatile avr32_pio_t *piob = &AVR32_PIOB;


int main (int argc, char *argv[]) {
  initNotes();
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

    /* Set up PIO for use by ABDAC. */

    /* Disable pins 20 and 21 on PIOB. */
    piob->PDR.p20 = 1;
    piob->PDR.p21 = 1;

    /* Grant control of those pins to peripheral A. */
    piob->ASR.p20 = 1;
    piob->ASR.p21 = 1;

    /* Set up power manager for use by ABDAC. */
    volatile avr32_pm_t *pm = &AVR32_PM;
    pm->GCCTRL[6].diven = 0;
    pm->GCCTRL[6].pllsel = 0;
    pm->GCCTRL[6].oscsel = 1;
    pm->GCCTRL[6].cen = 1;

    /* Set up the ABDAC. */
    volatile avr32_abdac_t *dac = &AVR32_ABDAC;
    dac->CR.en = 1;
    dac->IER.tx_ready = 1;
}

int freq = 220;

void button_isr(void)
{
    /* Do debouncing before reading the data pins. */
    volatile int k = 1000;
    while (k--);

    volatile avr32_pio_t *pio = &AVR32_PIOB;
    int isr = pio->isr,
        pdsr = pio->pdsr;
    int i, j;
    for (i = 0; i < 8; i++) {
        if ((isr & (1 << i)) && (~pdsr & (1 << i))) {
            freq = notes[i];
        }
    }
}

int step = 0;
int rate = 46875 >> 3;
int amp = 65535;

double sin_lookup(double x)
{
    static double *lookup;
    static const int length = 720;
    int i;

    if (lookup == NULL) {
        lookup = malloc(length * sizeof(double));
        for (i = 0; i < length; i++) {
            lookup[i] = sin(i * (2*M_PI) / length);
        }
    }

    return lookup[(int)((x - ((int)(x/(2*M_PI)))*(2*M_PI)) * length / (2*M_PI))];
}

void abdac_isr(void)
{
    volatile avr32_abdac_t *dac = &AVR32_ABDAC;
    dac->SDR.channel0 = (short)(sin_lookup(step * (2*M_PI) * freq / rate) * amp / 10);
    dac->SDR.channel1 = (short)(sin_lookup(step * (2*M_PI) * freq / rate) * amp / 10);

    step++;
    if (step * freq >= rate)
        step = 0;
}
