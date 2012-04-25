#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "image.h"

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

image_t *image_load(char *filename)
{
    int file, data_start;
    tga_header_t header;
    image_t *image;

    image = malloc(sizeof(image_t));

    file = open(filename, O_RDONLY);
    read(file, &header, sizeof(header));
//    header.width = header.width << 8 | header.width >> 8;
//    header.height = header.height << 8 | header.height >> 8;

    data_start = sizeof(header) + header.id_length + header.color_map_length;
    printf("width 0x%hx height 0x%hx", ((short*)&header)[6], header.height);

    image->width = header.width;
    image->height = header.height;
    image->data = mmap(0,  header.width * header.height * 4, PROT_READ,
        MAP_SHARED, file, data_start);

    return image;
}

void image_draw(int x, int y, image_t *image)
{
    int i, j;
    for (i = 0; i < image->width; i++)
        for (j = 0; j < image->height; j++)
            screen_put(x + i, y + j, image->data[y * image->width + x]);
}
