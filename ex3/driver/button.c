#include "ap7000.h"
#include "button.h"

volatile avr32_pio_t *btn_pio = &AVR32_PIOB;

void btn_init(void)
{
    volatile int isr;
    btn_pio->per |= 0xff;
    btn_pio->puer |= 0xff;
    btn_pio->ier |= 0xff;
    isr = btn_pio->isr;
}

char btn_read(void)
{
    return ~btn_pio->pdsr;
}
