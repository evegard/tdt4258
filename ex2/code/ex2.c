#include <stdlib.h>
#include <math.h>

#include <avr32/ap7000.h>
#include <sys/interrupts.h>

#include "ex2.h"
#include "sound.h"
#include "melody.h"
#include "led.h"
#include "button.h"

/* Program entry point. */
int main (int argc, char *argv[])
{
    /* Initialize interrupts. */
    int_init();
    /* Initialize LEDs. */
    led_init();
    /* Initialize buttons. */
    btn_init();
    /* Initialize sound. */
    snd_init();

    /* Enter the melody play loop. */
    mel_play_loop();

    return 0;
}

/* Initialize interrupts. */
void int_init()
{
    /* Call into the AVR library to set up interrupt handling. */
    set_interrupts_base((void *)AVR32_INTC_ADDRESS);
    init_interrupts();
}
