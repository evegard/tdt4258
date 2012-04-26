#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "image.h"

#pragma pack(push)
#pragma pack(1)
typedef struct tga_header {
    char id_length;
    char color_map_type;
    char image_type;

    short color_map_offset;
    short color_map_length;
    char color_map_entry_size;

    short x_origin;
    short y_origin;
    short width;
    short height;
    char depth;
    char image_descriptor;
} tga_header_t;
#pragma pack(pop)

image_t *image_load(char *filename)
{
    int file, data_start, data_length;
    tga_header_t *header;
    image_t *image;

    header = malloc(sizeof(tga_header_t));
    image = malloc(sizeof(image_t));

    file = open(filename, O_RDONLY);
    read(file, header, sizeof(tga_header_t));

    header->width = (header->width >> 8 & 0xff) | header->width << 8;
    header->height = (header->height >> 8 & 0xff) | header->height << 8;

    data_start = sizeof(tga_header_t) + header->id_length +
        header->color_map_length;
    data_length = header->width * header->height * 3 + data_start;

    image->width = header->width;
    image->height = header->height;
    image->data = mmap(0, data_length, PROT_READ, MAP_SHARED, file, 0) +
        data_start;

    return image;
}

void image_draw(int x, int y, image_t *image)
{
    int i, j;
    color_t *color;
    for (i = 0; i < image->width; i++)
        for (j = 0; j < image->height; j++) {
            color = &image->data[j * image->width + i];
            if (color->r == color_purple.r &&
                color->g == color_purple.g &&
                color->b == color_purple.b)
                continue;
            screen_put(x + i, y + (image->height - 1 - j), *color);
        }
}
