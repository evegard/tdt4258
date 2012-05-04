#ifndef LED_H
#define LED_H

extern char led_setup;

/*
 * Initializes the LED-drivers and settings such that other
 * LED-functions work properly.
 */
void led_init(void);

/*
 * Updates the LED-setup to the current setup by writing to the device
 * driver.
 */
void led_update(void);

/*
 * Sets the LED at position i to the value of on. i must be in the range
 * 0-7, and on must be either 0 for off or 1 for on. Will update the LED
 * setup after the LED is set.
 */
void led_set(int i, int on);

/*
 * Gets the value of the LED at position i on the STK1000 board. Returns
 * either 0 or 1: 1 if the LED is set, and 0 if the LED is not set.
 */
int led_get(int i);

/*
 * Will set the LED-setup to 0 and update the LEDs. Is equivalent to
 * setting all LED-lights off sequentially, but potentially more
 * efficient.
 */
void led_clear(void);

#endif
