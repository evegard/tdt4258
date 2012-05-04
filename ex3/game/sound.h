#ifndef SOUND_H
#define SOUND_H

/*
 * Will initialize the sound unit and set up the proper sound rate and
 * sound size. 
 */
void snd_init();

/*
 * Will play the sound as a raw format from the filename given as input.
 * If the previous sound given to this function is still running, this
 * function will stop the sound and start this one.
 */
void snd_play(char *filename);

/*
 * Will play the sound as a raw format from the filename given as input,
 * and block until the sound has finished playing.  If the previous
 * sound given to this function is still running, this function will
 * stop the sound and start this sound.
 */
void snd_play_wait(char *filename);

#endif
