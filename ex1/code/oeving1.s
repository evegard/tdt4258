/*******************************************************************************
 *
 * TDT4258 Microcontrollers
 * Exercise 1
 *
 ******************************************************************************/

.include "io.s"

/******************************************************************************/
/* Text segment                                                               */
/******************************************************************************/

.text

.globl  _start
_start:
        /* Set up registers. */

        /* r0: Base address for PIOB. */
        lddpc r0, piob
        /* r1: Base address for PIOC. */
        lddpc r1, pioc
        /* r2: Base address for INTC. */
        lddpc r2, intc

        /* r8: Scratch register. */
        /* r9: Scratch register II. */

        /* r11: Constantly 0xff. */
        mov r11, 0xff
        /* r12: Current LED setup. */
        mov r12, 1

        /* Set up IO registers. */

        /* Set up buttons. */

        /* Put bit mask in r8 for pins 0 and 2. */
        mov r8, 5
        /* Enable PIOB pins 0 and 2. */
        st.w r0[AVR32_PIO_PER], r8
        /* Set pull-up mode for PIOB pins 0 and 2. */
        st.w r0[AVR32_PIO_PUER], r8
        /* Enable interrupts for PIOB pins 0 and 2. */
        st.w r0[AVR32_PIO_IER], r8

        /* Set up LEDs. */

        /* Enable PIOC pins 0-7. */
        st.w r1[AVR32_PIO_PER], r11
        /* Set output mode for PIOC pins 0-7. */
        st.w r1[AVR32_PIO_OER], r11

        /* Set up interrupt handling. */

        /* Set EVBA to 0. */
        mov r8, 0
        mtsr 4, r8

        /* Point autovector to interrupt_handler for interrupt group 14
         * (which is PIOB). */
        mov r8, interrupt_handler
        st.w r2[AVR32_INTC_IPR14], r8

        /* Read the Interrupt Status Register for PIOB to clear pending
         * interrupts. */
        ld.w r8, r0[AVR32_PIO_ISR]

        /* Enable interrupts in the CPU. */
        csrf 16

        /* Main loop that sets up the LEDs according to r12 and then
         * sleeps (stops the processor until an interrupt arrives). */
mainloop:
        /* Clear the LEDs. */
        st.w r1[AVR32_PIO_CODR], r11
        /* Set the LEDs according ro r12. */
        st.w r1[AVR32_PIO_SODR], r12

        /* Put the processor to sleep. */
        sleep 0
        /* Loop. */
        rjmp mainloop

        /* The interrupt handler. */
interrupt_handler:
        /* Loop 1000 times to avoid bouncing. */
        mov r8, 1000
interrupt_handler_sleep_start:
        sub r8, 1
        cp.w r8, 0
        breq interrupt_handler_sleep_end
        rjmp interrupt_handler_sleep_start
interrupt_handler_sleep_end:

        /* Read the Interrupt Status Register for PIOB. */
        ld.w r8, r0[AVR32_PIO_ISR]
        /* Check whether the right button generated the interrupt. */
        mov r9, 0b00000001
        and r8, r8, r9
        cp.w r8, r9
        /* If so, jump to its part of the interrupt handler. */
        breq interrupt_button_right

        /* Handle the left button. */
interrupt_button_left:
        /* Read the data pins of the buttons. */
        ld.w r8, r0[AVR32_PIO_PDSR]
        /* Compare to see whether the left button is pushed down. */
        mov r9, 0b100
        and r8, r8, r9
        cp.w r8, r9
        /* If the left button is not pushed down, skip to the end of the
         * interrupt handler. */
        breq interrupt_end

        /* Check whether we are already at the leftmost LED, and if so,
         * skip to the end of the interrupt handler. */
        cp.w r12, 0b10000000
        breq interrupt_end

        /* Clear the carry register to make rol rotate a 0. */
        csrf 0 
        /* Rotate the LED setup one step to the left. */
        rol r12
        /* Skip to the end of the interrupt handler. */
        rjmp interrupt_end

        /* Handle the right button. */
interrupt_button_right:
        /* Read the data pins of the buttons. */
        ld.w r8, r0[AVR32_PIO_PDSR]
        /* Compare to see whether the right button is pushed down. */
        mov r9, 0b00000001
        and r8, r8, r9
        cp.w r8, r9
        /* If the right button is not pushed down, skip to the end of
         * the interrupt handler. */
        breq interrupt_end

        /* Check whether we are already at the rightmost LED, and if so,
         * skip to the end of the interrupt handler. */
        cp.w r12, 0b00000001
        breq interrupt_end

        /* Rotate the LED setup one step to the right. */
        ror r12

interrupt_end:
        /* Return from the interrupt handler. */
        rete

        /* Various constants. */
piob: 
        .int AVR32_PIOB
pioc: 
        .int AVR32_PIOC
intc: 
        .int AVR32_INTC
