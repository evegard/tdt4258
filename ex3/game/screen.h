#ifndef SCREEN_H
#define SCREEN_H

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240


/*
 * color_t is a type which represents a pixel on the framebuffer. The
 * characters b, g and r represents the colors blue, green and red,
 * respectively.
 */
typedef struct color {
    char b;
    char g;
    char r;
} color_t;

extern color_t *screen;
extern color_t *screen_buffer;

extern color_t color_red, color_green, color_blue, color_purple,
               color_black;
/*
 * Opens the device driver to the framebuffer and initializes the screen
 * and screen buffer arrays.
 */
void screen_init(void);

/*
 * Copies the data from the screen buffer onto the screen.
 */
void screen_show_buffer(void);

/*
 * Clears the whole screen buffer and sets the colour of every pixel to
 * the color provided.
 */
void screen_clear(color_t color);

/*
 * Draws a line from the position (xs, ys) to the position (xe, ye) with
 * the color provided onto the screen buffer.
 */
void screen_line(int xs, int ys, int xe, int ye, color_t color);

/*
 * Draws an empty rectangle (border only) with width width and height
 * height with the color provided onto the screen buffer. The
 * rectangle's upper left corner is located at position (x,y).
 */
void screen_rectangle(int x, int y, int width, int height, color_t color);

/*
 * Draws a filled rectangle in the same fashion as the function
 * screen_rectangle works.
 */
void screen_fill_rectangle(int x, int y, int width, int height, color_t color);


/*
 * Puts the color color in the screen buffer at location (x,y).
 */
#define screen_put(x, y, color) (screen_buffer[(y) * SCREEN_WIDTH + (x)] = (color))

#endif
