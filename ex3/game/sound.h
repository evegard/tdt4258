#ifndef SOUND_H
#define SOUND_H

#define SND_RATE    44100
#define SND_SIZE    16
#define SND_AMP     255

extern int snd_buffer_step;

extern short *snd_buffer;
extern int snd_buffer_len;

void snd_init();
int snd_note_buffer_len(double frequency);
short* snd_note_buffer(double frequency);
void snd_replace_buffer(short *new_buffer, int new_buffer_len);
void *snd_play_loop(void *arg);

#endif
