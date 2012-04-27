#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "button.h"

int btn_file;

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
    volatile int j;
    if ((btn_read() & (1 << i)) == 0)
        return 0;
    for (j = 0; j < 1000; j++);
    return (btn_read() & (1 << i)) != 0;
}
