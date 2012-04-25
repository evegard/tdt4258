#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "screen.h"

color_t *screen;
color_t *screen_buffer;
int fb;

color_t color_red = { 0, 0, 255 },
        color_green = { 0, 255, 0 },
        color_blue = { 255, 0, 0 };

void screen_bouncer()
{
    int x = 0, y = 0, dx = 1, dy = 1, w = 50, h = 100;
    while (1) {
        screen_clear(color_red);
        screen_rectangle(x, y, w, h, color_green);
        screen_line(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
            x + w / 2, y + h / 2, color_blue);
        screen_show_buffer();
        if (y + h == SCREEN_HEIGHT && dy == 1) dy = -1;
        if (y == 0 && dy == -1) dy = 1;
        if (x + w == SCREEN_WIDTH && dx == 1) dx = -1;
        if (x == 0 && dx == -1) dx = 1;
        x += dx; y += dy;
    }
}

void screen_init(void)
{
    fb = open("/dev/fb0", O_RDWR);
    screen = mmap(0,  SCREEN_WIDTH * SCREEN_HEIGHT * 3, PROT_WRITE,
        MAP_SHARED, fb, 0);

    screen_buffer = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * 3);

    screen_bouncer();
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
