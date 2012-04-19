#ifndef MELODY_H
#define MELODY_H

/* Two octaves of notes at disposal. */

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

#define C5       13
#define C5_SHARP 14
#define D5       15
#define D5_SHARP 16
#define E5       17
#define F5       18
#define F5_SHARP 19
#define G5       20
#define G5_SHARP 21
#define A5       22
#define A5_SHARP 23
#define B5       24

/* The array containing the notes of the currently playing melody. */
extern int *mel_notes;
/* The array containing the note lengths of the currently playing melody. */
extern int *mel_notelens;
/* The length of the two previous arrays. */
extern int mel_size;

/* The index of the currently playing note. */
extern int mel_cur_note;
/* The amount of samples played for the currently playing note. */
extern int mel_cur_note_step;

/* Get the frequency of the given note. */
int mel_get_note_freq(int note);
/* The melody play loop. */
void mel_play_loop();
/* Change the currently playing melody. */
void mel_set_melody(int melody);

#endif
