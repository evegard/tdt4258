#ifndef LED_H
#define LED_H

#include <avr32/ap7000.h>

extern int led_setup;

void led_init();
void led_update();
void led_set(int i, int on);
int led_get(int i);
void led_clear();

#endif
