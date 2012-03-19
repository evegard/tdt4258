#ifndef LED_H
#define LED_H

/* The current LED setup. */
extern int led_setup;

/* Initialize LED I/O. */
void led_init();
/* Update the LEDs according to 'led_setup'. */
void led_update();
/* Set the value of a specific LED. */
void led_set(int i, int on);
/* Get the state of a specific LED. */
int led_get(int i);
/* Clear all LEDs. */
void led_clear();

#endif
