#include <stdlib.h>
#include <math.h>

#include "melody.h"
#include "sound.h"
#include "led.h"

int *mel_notes = NULL;
int *mel_notelens = NULL; 
int mel_size = 0;

int mel_cur_note = 0;
int mel_cur_note_step = 0;

int mel_get_note_freq(int note)
{
    return 440 * pow(2, (note - 10) / 12.0);
}

void mel_play_loop()
{
    while (1) {
        int note_freq, new_snd_buffer_len;
        short *new_snd_buffer;

        while (mel_cur_note >= mel_size);

        if (mel_notes[mel_cur_note] != 0) {
            note_freq = mel_get_note_freq(mel_notes[mel_cur_note]);

            new_snd_buffer = snd_note_buffer(note_freq);
            new_snd_buffer_len = snd_note_buffer_len(note_freq);
        } else {
            new_snd_buffer_len = 1;
            new_snd_buffer = malloc(new_snd_buffer_len * sizeof(short));
            new_snd_buffer[0] =  0;
        }

        snd_replace_buffer(new_snd_buffer, new_snd_buffer_len);
        mel_cur_note_step = 0;

        while (mel_cur_note_step < mel_notelens[mel_cur_note] * SND_RATE / 64);

        mel_cur_note++;
        if (mel_cur_note >= mel_size) {
            led_clear();
        }
    }
}

void mel_set_melody(int melody)
{
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

    mel_cur_note = 0;
    led_clear();
    led_set(melody, 1);
}
