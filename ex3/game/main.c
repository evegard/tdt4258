#include "screen.h"
#include "image.h"

int main(void)
{
    image_t *titlescreen;

    screen_init();
    titlescreen = image_load("images/tittel.tga");
    image_draw(0, 0, titlescreen);
    return 0;
}
