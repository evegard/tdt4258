#ifndef SOUND_H
#define SOUND_H

#include <avr32/ap7000.h>

#define SND_RATE    12000000 / 256

extern int snd_buffer_step;
extern int snd_amp;

extern short *snd_buffer;
extern int snd_buffer_len;

int snd_note_buffer_len(double frequency);
short* snd_note_buffer(double frequency);
void snd_replace_buffer(short *new_buffer, int new_buffer_len);

void abdac_isr(void);

#endif
