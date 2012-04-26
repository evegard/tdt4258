#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "led.h"

char led_setup = 0;
int led_file;

void led_init(void)
{
    led_file = open("/dev/stkboard", O_WRONLY);
}

void led_update(void)
{
    write(led_file, &led_setup, 1);
}

void led_set(int i, int on)
{
    on &= 1;
    led_setup &= ~(1 << i);
    led_setup |= (on << i);
    led_update();
}

int led_get(int i)
{
    return (led_setup & (1 << i)) != 0;
}

void led_clear(void)
{
    led_setup = 0;
    led_update();
}
