#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <signal.h>

#include "sound.h"

#define SND_RATE    22050
#define SND_SIZE    16

int snd_device;
pthread_t snd_cur_thread;
static volatile sig_atomic_t snd_prev_sound_finished;
static volatile sig_atomic_t snd_stop_current_sound;

void *snd_play_loop(void *arg);

void snd_init()
{
    int temp;
    
    snd_prev_sound_finished = 1;
    snd_stop_current_sound = 0;

    snd_device = open("/dev/dsp", O_WRONLY);

    temp = SND_SIZE;
    ioctl(snd_device, SOUND_PCM_WRITE_BITS, &temp);

    temp = SND_RATE;
    ioctl(snd_device, SOUND_PCM_WRITE_RATE, &temp);
}

void snd_play(char *filename)
{
    if (!snd_prev_sound_finished) {
        snd_stop_current_sound = 1;
    }
    pthread_create(&snd_cur_thread, 0, snd_play_loop, filename);
}

void snd_play_wait(char *filename)
{
    snd_play(filename);
    pthread_join(snd_cur_thread, NULL);
}

void *snd_play_loop(void *arg)
{
    snd_prev_sound_finished = 0;
    
    int file;
    struct stat st;
    short *buffer;
    int buffer_len;
    int buffer_step;
    
    file = open((char *)arg, O_RDONLY);
    fstat(file, &st);

    buffer = mmap(0, st.st_size, PROT_READ, MAP_SHARED, file, 0);
    buffer_len = st.st_size / (SND_SIZE / 8);
    buffer_step = 0;

    while (buffer_step < buffer_len) {
        write(snd_device, &buffer[buffer_step], (SND_SIZE / 8));
        buffer_step++;
        if (snd_stop_current_sound)
            break;
    }

    munmap(buffer, st.st_size);
    close(file);

    snd_prev_sound_finished = 1;
    snd_stop_current_sound = 0;
    return 0;
}
