#ifndef SOUND_H
#define SOUND_H

/* The sample rate. */
#define SND_RATE    (20000000 / 256)
/* The maximum amplitude to use. */
#define SND_AMP     (32767 / 2)

/* The current index into the current sample buffer. */
extern int snd_buffer_step;

/* The current sample buffer. */
extern short *snd_buffer;
/* The length of the current sample buffer. */
extern int snd_buffer_len;

/* Initialize the ABDAC and related components. */
void snd_init();
/* Get the required sample buffer length for a note of the given frequency. */
int snd_note_buffer_len(double frequency);
/* Create a sample buffer for a note of the given frequency. */
short* snd_note_buffer(double frequency);
/* Change the currently playing sample buffer. */
void snd_replace_buffer(short *new_buffer, int new_buffer_len);

/* The ABDAC sample interrupt routine. */
void snd_interrupt();

#endif
