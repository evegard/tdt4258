#include <pthread.h>

#include "screen.h"
#include "image.h"
#include "led.h"
#include "button.h"
#include "sound.h"
#include "melody.h"
#include "ui.h"

int main(void)
{
    pthread_t thread;

    screen_init();
    led_init();
    btn_init();
    snd_init();

    //pthread_create(&thread, 0, snd_play_loop, 0);
    //pthread_create(&thread, 0, mel_play_loop, 0);
    //mel_set_melody(0);

    ui_run();

    return 0;
}
