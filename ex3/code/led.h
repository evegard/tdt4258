#ifndef LED_H
#define LED_H

extern int led_setup;

void led_init(void);
void led_update(void);
void led_set_all(int new_setup);

#endif
