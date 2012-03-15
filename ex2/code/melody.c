#include <stdlib.h>
#include <math.h>

#include "melody.h"
#include "sound.h"

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

        if (mel_cur_note >= mel_size)
            continue;

        if (mel_notes[mel_cur_note] != 0) {
            note_freq = mel_get_note_freq(mel_notes[mel_cur_note]);

            new_snd_buffer = snd_note_buffer(note_freq);
            new_snd_buffer_len = snd_note_buffer_len(note_freq);
        } else {
            new_snd_buffer_len = 2;
            new_snd_buffer = malloc(new_snd_buffer_len * sizeof(short));
            new_snd_buffer[0] =  1;
            new_snd_buffer[1] = -1;
        }

        snd_replace_buffer(new_snd_buffer, new_snd_buffer_len);

        while (mel_cur_note_step <
            mel_notelens[mel_cur_note] * SND_RATE / 16);
        mel_cur_note++;
    }
}

void mel_set_melody(int melody)
{
    static int petter_notes[] = {
        C,0,C,0,C,0,D,0,E,0,E,0,E,0,E,0,D,0,C,0,D,0,E,0,C,0};
    static int petter_notelens[] = {
        4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1};
    static int petter_size = sizeof(petter_notes) / sizeof(int);

    switch (melody) {
        case 1:
            mel_notes = petter_notes;
            mel_notelens = petter_notelens;
            mel_size = petter_size;
            break;
            
        default:
            mel_notes = NULL;
            mel_notelens = NULL;
            mel_size = 0;
            break;
    }

    mel_cur_note = 0;
}
