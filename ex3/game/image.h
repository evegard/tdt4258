#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "screen.h"

typedef struct image {
    int width;
    int height;
    color_t *data;
} image_t;

image_t *image_load(char *filename);
void image_draw(int x, int y, image_t *image);

#endif
