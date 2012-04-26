#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#include "sound.h"
#include "melody.h"

#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif

int snd_file;

int snd_buffer_step = 0;

short *snd_buffer = NULL;
int snd_buffer_len = 0;

void snd_init()
{
    int temp;

    snd_file = open("/dev/dsp", O_WRONLY);

    temp = SND_SIZE;
    ioctl(snd_file, SOUND_PCM_WRITE_BITS, &temp);

    temp = SND_RATE;
    ioctl(snd_file, SOUND_PCM_WRITE_RATE, &temp);
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

void *snd_play_loop(void *arg)
{
    while (1) {
        if (snd_buffer_step >= snd_buffer_len) {
            snd_buffer_step = 0;
        }

        if (snd_buffer_len) {
            write(snd_file, &snd_buffer[snd_buffer_step], 2);
        } else {
            int buffer = 0;
            write(snd_file, &buffer, 2);
        }
        
        snd_buffer_step++;
        mel_cur_note_step++;
    }
    return 0;
}
