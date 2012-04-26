#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "screen.h"
#include "image.h"

color_t *screen;
color_t *screen_buffer;
int fb;

color_t color_red = { 0, 0, 255 },
        color_green = { 0, 255, 0 },
        color_blue = { 255, 0, 0 },
        color_purple = { 255, 0, 255 };

void screen_init(void)
{
    fb = open("/dev/fb0", O_RDWR);
    screen = mmap(0,  SCREEN_WIDTH * SCREEN_HEIGHT * 3, PROT_WRITE,
        MAP_SHARED, fb, 0);

    screen_buffer = calloc(SCREEN_WIDTH * SCREEN_HEIGHT, 3);
    screen_show_buffer();
}

void screen_show_buffer(void)
{
    memcpy(screen, screen_buffer, SCREEN_WIDTH * SCREEN_HEIGHT * 3);
}

void screen_clear(color_t color)
{
    screen_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}

void screen_rectangle(int x, int y, int width, int height, color_t color)
{
    int i, j;
    for (i = x; i < x + width; i++)
        for (j = y; j < y + height; j++)
            screen_put(i, j, color);
}

void screen_line(int xs, int ys, int xe, int ye, color_t color)
{
    int dx = abs(xe - xs);
    int dy = abs(ye - ys);
    int sx = xs < xe ? 1 : -1;
    int sy = ys < ye ? 1 : -1;
    int err = dx - dy;

    while (1) {
        screen_put(xs, ys, color);
        if (xs == xe && ys == ye)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            xs += sx;
        }
        if (e2 <  dx) {
            err += dx;
            ys += sy;
        }
    }
}
