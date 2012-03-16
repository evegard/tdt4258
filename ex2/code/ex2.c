#include <stdlib.h>
#include <math.h>

#include <avr32/ap7000.h>
#include <sys/interrupts.h>

#include "ex2.h"
#include "sound.h"
#include "melody.h"
#include "led.h"
#include "button.h"

int main (int argc, char *argv[])
{
    int_init();
    led_init();
    btn_init();
    snd_init();

    mel_play_loop();

    return 0;
}

void int_init()
{
  set_interrupts_base((void *)AVR32_INTC_ADDRESS);
  init_interrupts();
}
