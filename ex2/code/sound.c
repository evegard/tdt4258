#include <stdlib.h>
#include <math.h>

#include <avr32/ap7000.h>
#include <sys/interrupts.h>

#include "sound.h"
#include "melody.h"

#define SND_INT_LEVEL 0

#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif

/* Set a pointer to the location of ABDAC control registers. */
volatile avr32_abdac_t *dac = &AVR32_ABDAC;

/* The current index into the current sample buffer. */
int snd_buffer_step = 0;

/* The current sample buffer. */
short *snd_buffer = NULL;
/* The length of the current sample buffer. */
int snd_buffer_len = 0;

/* Initialize the ABDAC and related components. */
void snd_init()
{
    /* Register 'snd_interrupt' as the ABDAC's interrupt routine. */
    register_interrupt(
        snd_interrupt,
        AVR32_ABDAC_IRQ / 32,
        AVR32_ABDAC_IRQ % 32,
        SND_INT_LEVEL);

    /* Set a pointer to the location of PIOB control registers. */
    volatile avr32_pio_t *piob = &AVR32_PIOB;

    /* Disable pins 20 and 21 on PIOB. */
    piob->PDR.p20 = 1;
    piob->PDR.p21 = 1;

    /* Grant control of those pins to peripheral A. */
    piob->ASR.p20 = 1;
    piob->ASR.p21 = 1;

    /* Set up power manager for use by ABDAC. */
    volatile avr32_pm_t *pm = &AVR32_PM;
    pm->GCCTRL[6].diven = 0;    /* Don't divide the frequency. */
    pm->GCCTRL[6].pllsel = 0;   /* Don't select the PLL. */
    pm->GCCTRL[6].oscsel = 0;   /* Select oscillator 0. */
    pm->GCCTRL[6].cen = 1;      /* Enable the clock. */

    /* Set up the ABDAC. */
    dac->CR.en = 1;
    dac->IER.tx_ready = 1;
}

/* Get the required sample buffer length for a note of the given frequency. */
int snd_note_buffer_len(double frequency)
{
    return SND_RATE / frequency;
}

/* Create a sample buffer for a note of the given frequency. */
short* snd_note_buffer(double frequency)
{
    /* Calculate the required buffer length. */
    int len = snd_note_buffer_len(frequency);
    /* Allocate memory for the buffer. */
    short *buffer = malloc(len * sizeof(short));
    int i;

    /* Loop through one cycle of the sine wave. */
    for (i = 0; i < len; i++) {
        /* Calculate the sample. */
        buffer[i] = sin(i * 2 * M_PI / len) * SND_AMP;
    }

    return buffer;
}

/* Change the currently playing sample buffer. */
void snd_replace_buffer(short *new_buffer, int new_buffer_len)
{
    short *old_buffer;

    /* Change the variables around. */
    snd_buffer_len = MIN(snd_buffer_len, new_buffer_len);
    old_buffer = snd_buffer;
    snd_buffer = new_buffer;
    snd_buffer_len = new_buffer_len;

    /* Free the old sample buffer. */
    free(old_buffer);
}

/* The ABDAC sample interrupt routine. */
void snd_interrupt(void)
{
    /* Check whether we need to loop back to the beginning of the buffer. */
    if (snd_buffer_step >= snd_buffer_len) {
        snd_buffer_step = 0;
    }

    /* Check whether we acutally have a sample buffer. */
    if (snd_buffer_len) {
        /* Yes -- read values from the sample buffer into the ABDAC's
         * sample register. */
        dac->SDR.channel0 = (short)(snd_buffer[snd_buffer_step]);
        dac->SDR.channel1 = (short)(snd_buffer[snd_buffer_step]);
    } else {
        /* No -- put zero values into the ABDAC's sample register. */
        dac->SDR.channel0 = 0;
        dac->SDR.channel1 = 0;
    }
    
    /* Increment the sample buffer index. */
    snd_buffer_step++;
    /* Increment the sample counter for the currently playing note. */
    mel_cur_note_step++;
}
