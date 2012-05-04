#ifndef IMAGE_H
#define IMAGE_H

#include "screen.h"

/*
 * The image_t type is a type which contains the width and height of the
 * image, as well as the image data as an array of color_t elements. The
 * image data array is of side width * height.
 */
typedef struct image {
    int width;
    int height;
    color_t *data;
} image_t;

/*
 * Loads an image from the filename provided and returns an image_t
 * which contain the image data. The image file must be a 24-bit
 * uncompressed TARGA format.
 */
image_t *image_load(char *filename);

/*
 * Draws an image in the screen buffer, where the upper left corner of
 * the image is placed at position (x, y).
 */
void image_draw(int x, int y, image_t *image);

#endif
