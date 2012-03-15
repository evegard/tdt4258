#include <stdlib.h>
#include <math.h>

#include "sound.h"
#include "melody.h"

#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif

int snd_buffer_step = 0;
int snd_amp = 65535 / 10;

short *snd_buffer = NULL;
int snd_buffer_len = 0;

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
        buffer[i] = sin(i * 2 * M_PI / len) * snd_amp;
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
    mel_cur_note_step = 0;

    free(old_buffer);
}

void abdac_isr(void)
{
    volatile avr32_abdac_t *dac = &AVR32_ABDAC;

    if (snd_buffer_step >= snd_buffer_len) {
        snd_buffer_step = 0;
    }

    if (snd_buffer_len) {
        dac->SDR.channel0 = (short)snd_buffer[snd_buffer_step];
        dac->SDR.channel1 = (short)snd_buffer[snd_buffer_step];
    } else {
        dac->SDR.channel0 = 0;
        dac->SDR.channel1 = 0;
    }
    
    snd_buffer_step++;
    mel_cur_note_step++;
}
