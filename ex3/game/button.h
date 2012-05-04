#ifndef BUTTON_H
#define BUTTON_H

extern int btn_ignore;

/*
 * Initializes button reading, so that it is possible to read all
 * buttons through btn_read or some specific button with btn_is_pushed.
 */
void btn_init(void);

/*
 * Reads the bitmask of the currently pushed buttons on the STK1000
 * board. Button 0 is on if bit 0 is 1, button 7 is on if bit 7 is on,
 * and so forth.
 */
char btn_read(void);

/*
 * Returns 1 if button i is pushed, otherwise returns 0. Will only
 * return 1 once for each button push: If the button is held
 * down, this function will only return true once, and will return false
 * until the button is released and pushed again.
 */
int btn_is_pushed(int i);

#endif
