#include <pthread.h>

#include "screen.h"
#include "image.h"
#include "led.h"
#include "button.h"
#include "sound.h"
#include "ui.h"

int main(void)
{
    screen_init();
    led_init();
    btn_init();
    snd_init();

    ui_run();

    return 0;
}
