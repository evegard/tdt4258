#include <pthread.h>

#include "screen.h"
#include "image.h"
#include "led.h"
#include "button.h"
#include "sound.h"
#include "melody.h"

void bouncer()
{
    image_t *background, *box;
    int x = 0, y = 0, dx = 1, dy = 1, w = 20, h = 20, i;

    background = image_load("images/tittel.tga");
    box = image_load("images/soldat.tga");
    while (1) {
        image_draw(0, 0, background);
        image_draw(x, y, box);
        screen_line(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
            x + w / 2, y + h / 2, color_blue);
        screen_show_buffer();
        if (y + h == SCREEN_HEIGHT && dy == 1) dy = -1;
        if (y == 0 && dy == -1) dy = 1;
        if (x + w == SCREEN_WIDTH && dx == 1) dx = -1;
        if (x == 0 && dx == -1) dx = 1;
        x += dx; y += dy;

        for (i = 0; i < 8; i++)
            led_set(i, btn_is_pushed(i));
    }
}

int main(void)
{
    pthread_t thread;

    screen_init();
    led_init();
    btn_init();
    snd_init();

    pthread_create(&thread, 0, snd_play_loop, 0);
    pthread_create(&thread, 0, mel_play_loop, 0);

    mel_set_melody(0);
    bouncer();

    return 0;
}
