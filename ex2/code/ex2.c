/*****************************************************************************
 * 
 * Øving 2 UCSysDes
 *
 *****************************************************************************/

#include <stdlib.h>
#include <math.h>

#include "ex2.h"

#define C       1
#define C_SHARP 2
#define D       3
#define D_SHARP 4
#define E       5
#define F       6
#define F_SHARP 7
#define G       8
#define G_SHARP 9
#define A       10
#define A_SHARP 11
#define B       12

#define RATE    12000000 / 256

#define MIN(a, b)   ((a) < (b) ? (a) : (b))

int step = 0;
int amp = 65535 / 10;

short *snd_buffer = NULL;
int snd_buffer_len = 0;

int snd_note_buffer_len(double frequency)
{
    return RATE / frequency;
}

short* snd_note_buffer(double frequency)
{
    int len = snd_note_buffer_len(frequency);
    short *buffer = malloc(len * sizeof(short));
    int i;

    for (i = 0; i < len; i++) {
        buffer[i] = sin(i * 2 * M_PI / len) * amp;
    }

    return buffer;
}

int mel_notes[]    = {C,0,C,0,C,0,D,0,E,0,E,0,E,0,E,0,D,0,C,0,D,0,E,0,C,0};
int mel_notelens[] = {4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1};
int mel_size = sizeof(mel_notes) / sizeof(int);
int mel_cur_note = 0;
int mel_cur_note_step = 0;

int mel_get_note_freq(int note)
{
    return 440 * pow(2, (note - 10) / 12.0);
}

volatile avr32_pio_t *piob = &AVR32_PIOB;


int main (int argc, char *argv[]) {
    initHardware();

    while(1) {
        int note_freq, new_snd_buffer_len;
        short *new_snd_buffer, *old_snd_buffer;

        if (mel_cur_note >= mel_size)
            mel_cur_note = 0;

        if (mel_notes[mel_cur_note] != 0) {
            note_freq = mel_get_note_freq(mel_notes[mel_cur_note]);

            new_snd_buffer = snd_note_buffer(note_freq);
            new_snd_buffer_len = snd_note_buffer_len(note_freq);
        } else {
            new_snd_buffer_len = 2;
            new_snd_buffer = malloc(new_snd_buffer_len * sizeof(short));
            new_snd_buffer[0] =  1;
            new_snd_buffer[1] = -1;
        }

        snd_buffer_len = MIN(snd_buffer_len, new_snd_buffer_len);
        old_snd_buffer = snd_buffer;
        snd_buffer = new_snd_buffer;
        snd_buffer_len = new_snd_buffer_len;
        mel_cur_note_step = 0;

        free(old_snd_buffer);

        while (mel_cur_note_step < mel_notelens[mel_cur_note] * RATE / 8);
        mel_cur_note++;
    }

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

void button_isr(void)
{
    /* Do debouncing before reading the data pins. */
    volatile int k = 1000;
    while (k--);

    volatile avr32_pio_t *pio = &AVR32_PIOB;
    int isr = pio->isr,
        pdsr = pio->pdsr;
    int i;
    for (i = 0; i < 8; i++) {
        if ((isr & (1 << i)) && (~pdsr & (1 << i))) {
        }
    }
}

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

    if (step >= snd_buffer_len) {
        step = 0;
    }

    if (snd_buffer_len) {
        dac->SDR.channel0 = (short)snd_buffer[step];
        dac->SDR.channel1 = (short)snd_buffer[step];
    } else {
        dac->SDR.channel0 = 0;
        dac->SDR.channel1 = 0;
    }
    
    step++;
    mel_cur_note_step++;
}
