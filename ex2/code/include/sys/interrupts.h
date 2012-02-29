/*
 * Include file for libavr32b-interrupts - a library to
 * emulate an older version of avr32b framework.
 *
 * written by Ole Henrik Jahren <olehenja@alumni.ntnu.no>
 */

#ifndef SYS_INTERRUPTS_H_
#define SYS_INTERRUPTS_H_ 1

typedef void (*__int_handler)(void);

__int_handler register_interrupt(__int_handler handler, int group,
		int line, int priority);
void set_interrupts_base(void *addr);
void init_interrupts(void);

void panic(void);

#endif /* SYS_INTERRUPTS_H_ */
