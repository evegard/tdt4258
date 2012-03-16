#ifndef SOUND_H
#define SOUND_H

#include <avr32/ap7000.h>

#define ABDAC_INT_LEVEL 0

#define SND_RATE    (20000000 / 256)
#define SND_AMP     (32767 / 2)
#define SND_FADEOUT 100

extern int snd_buffer_step;

extern short *snd_buffer;
extern int snd_buffer_len;

void snd_init();
int snd_note_buffer_len(double frequency);
short* snd_note_buffer(double frequency);
void snd_replace_buffer(short *new_buffer, int new_buffer_len);

void abdac_isr(void);

#endif
