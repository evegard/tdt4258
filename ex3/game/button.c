#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "button.h"

int btn_file;
int btn_ignore = 0;

void btn_init()
{
    btn_file = open("/dev/stkboard", O_RDONLY);
}

char btn_read()
{
    char buffer;
    read(btn_file, &buffer, 1);
    return buffer;
}

int btn_is_pushed(int i)
{
    int is_pushed;
    volatile int j;

    is_pushed = (btn_read() & (1 << i)) != 0;

    if ((btn_ignore & (1 << i)) != 0) {
        if (!is_pushed) {
            btn_ignore &= ~(1 << i);
        }
        return 0;
    }

    if (!is_pushed)
        return 0;

    for (j = 0; j < 1000; j++);

    is_pushed = (btn_read() & (1 << i)) != 0;

    if (!is_pushed)
        return 0;

    btn_ignore |= 1 << i;
    return 1;
}
