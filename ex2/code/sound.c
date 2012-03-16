#include <stdlib.h>
#include <math.h>

#include <sys/interrupts.h>

#include "sound.h"
#include "melody.h"

#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif

volatile avr32_abdac_t *dac = &AVR32_ABDAC;

int snd_buffer_step = 0;

short *snd_buffer = NULL;
int snd_buffer_len = 0;

void snd_init()
{
    register_interrupt(
        abdac_isr,
        AVR32_ABDAC_IRQ / 32,
        AVR32_ABDAC_IRQ % 32,
        ABDAC_INT_LEVEL);

    /* Set up PIO for use by ABDAC. */
    volatile avr32_pio_t *piob = &AVR32_PIOB;

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
    pm->GCCTRL[6].oscsel = 0;
    pm->GCCTRL[6].cen = 1;

    /* Set up the ABDAC. */
    dac->CR.en = 1;
    dac->IER.tx_ready = 1;
}

int snd_note_buffer_len(double frequency)
{
    return SND_RATE / frequency;
}

short* snd_note_buffer(double frequency)
{
    int len = snd_note_buffer_len(frequency);
    short *buffer = malloc(len * sizeof(short));
    int i;

    for (i = 0; i < len; i++) {
        buffer[i] = sin(i * 2 * M_PI / len) * SND_AMP;
    }

    return buffer;
}

void snd_replace_buffer(short *new_buffer, int new_buffer_len)
{
    short *old_buffer;

    snd_buffer_len = MIN(snd_buffer_len, new_buffer_len);
    old_buffer = snd_buffer;
    snd_buffer = new_buffer;
    snd_buffer_len = new_buffer_len;

    free(old_buffer);
}

void abdac_isr(void)
{
    if (snd_buffer_step >= snd_buffer_len) {
        snd_buffer_step = 0;
    }

    if (snd_buffer_len) {
        dac->SDR.channel0 = (short)(snd_buffer[snd_buffer_step]);
        dac->SDR.channel1 = (short)(snd_buffer[snd_buffer_step]);
    } else {
        dac->SDR.channel0 = 0;
        dac->SDR.channel1 = 0;
    }
    
    snd_buffer_step++;
    mel_cur_note_step++;
}
