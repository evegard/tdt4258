#ifndef BUTTON_H
#define BUTTON_H

extern int btn_ignore;

void btn_init(void);
char btn_read(void);
int btn_is_pushed(int i);

#endif
