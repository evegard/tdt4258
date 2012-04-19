#include <stdlib.h>
#include <math.h>

#include "melody.h"
#include "sound.h"
#include "led.h"

/* The array containing the notes of the currently playing melody. */
int *mel_notes = NULL;
/* The array containing the note lengths of the currently playing melody. */
int *mel_notelens = NULL; 
/* The length of the two previous arrays. */
int mel_size = 0;

/* The index of the currently playing note. */
int mel_cur_note = 0;
/* The amount of samples played for the currently playing note. */
int mel_cur_note_step = 0;

/* Get the frequency of the given note. */
int mel_get_note_freq(int note)
{
    return 440 * pow(2, (note - 10) / 12.0);
}

/* The melody play loop. */
void mel_play_loop()
{
    /* Loop infinitely. */
    while (1) {
        int note_freq, new_snd_buffer_len;
        short *new_snd_buffer;

        /* If the current melody is done, do a busy wait until this changes. */
        while (mel_cur_note >= mel_size);

        /* Check whether we want to play a note or silence. */
        if (mel_notes[mel_cur_note] != 0) {
            /* We want to play a note -- get its frequency. */
            note_freq = mel_get_note_freq(mel_notes[mel_cur_note]);

            /* Create the sample buffer of the new note. */
            new_snd_buffer = snd_note_buffer(note_freq);
            new_snd_buffer_len = snd_note_buffer_len(note_freq);
        } else {
            /* We want to play some silence -- allocate a sample buffer
             * of length 1, containing a 0. */
            new_snd_buffer_len = 1;
            new_snd_buffer = malloc(new_snd_buffer_len * sizeof(short));
            new_snd_buffer[0] =  0;
        }

        /* Start playing the new sample buffer, and free the memory of
         * the old sample buffer. */
        snd_replace_buffer(new_snd_buffer, new_snd_buffer_len);
        /* Reset the sample counter of the current note. */
        mel_cur_note_step = 0;

        /* Do a busy wait until the current note is done playing. */
        while (mel_cur_note_step < mel_notelens[mel_cur_note] * SND_RATE / 64);

        /* Increment the current note index. */
        mel_cur_note++;
        /* If the current melody is done, clear the LEDs. */
        if (mel_cur_note >= mel_size) {
            led_clear();
        }
    }
}

/* Change the currently playing melody. */
void mel_set_melody(int melody)
{
    /* The note arrays of the four defined melodies. */
    static int intro_notes[] = {
        C,0,C,0,C,0,D,0,E,0,E,0,E,0,E,0,D,0,C,0,D,0,E,0,C,0,
        C,0,E,0,E,0,E,0,F,0,G,0,G,0,G,0,F,0,E,0,F,0,G,0,E,0,
        C5,0,C5,0,B,0,B,0,B,0,A,0,A,0,A,0,A,0,G,0,G,0,
        C,0,C,0,C,0,D,0,E,0,E,0,E,0,E,0,D,0,C,0,D,0,E,0,C,0 };
    static int intro_notelens[] = {
        8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,32,
        8,1,8,1,8,1,8,1,8,1,16,8,8,8,8,4,8,1,8,1,8,1,8,1,8,32,
        16,8,16,8,16,4,16,4,8,4,8,1,8,1,8,1,8,1,16,8,16,8,
        8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,8 };
    static int intro_size = sizeof(intro_notes) / sizeof(int);

    static int win_notes[] = {C,D,C5,0};
    static int win_notelens[] = {4,8,32,1};
    static int win_size = sizeof(win_notes) / sizeof(int);

    static int fire_notes[] = {G_SHARP,A_SHARP,B,0};
    static int fire_notelens[] = {4,8,32,1};
    static int fire_size = sizeof(fire_notes) / sizeof(int);

    static int hit_notes[] = {C_SHARP,D_SHARP,C_SHARP,D_SHARP,C_SHARP,D_SHARP,0};
    static int hit_notelens[] = {2,2,2,2,2,16,2};
    static int hit_size = sizeof(hit_notes) / sizeof(int);

    /* Select the melody to play and change the note arrays accordingly. */
    switch (melody) {
        case 0:
            mel_notes = intro_notes;
            mel_notelens = intro_notelens;
            mel_size = intro_size;
            break;
            
        case 1:
            mel_notes = win_notes;
            mel_notelens = win_notelens;
            mel_size = win_size;
            break;
            
        case 2:
            mel_notes = fire_notes;
            mel_notelens = fire_notelens;
            mel_size = fire_size;
            break;
            
        case 3:
            mel_notes = hit_notes;
            mel_notelens = hit_notelens;
            mel_size = hit_size;
            break;
            
        default:
            mel_notes = NULL;
            mel_notelens = NULL;
            mel_size = 0;
            break;
    }

    /* Start playing at the beginning of the melody. */
    mel_cur_note = 0;
    /* Clear the LEDs. */
    led_clear();
    /* Set the LED of the current melody. */
    led_set(melody, 1);
}
