#ifndef LED_H
#define LED_H

extern char led_setup;

void led_init(void);
void led_update(void);
void led_set(int i, int on);
int led_get(int i);
void led_clear(void);

#endif
