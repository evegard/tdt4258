/******************************************************************************
 *
 * TDT4258 Microcontrollers
 * Exercise 1
 *
 *****************************************************************************/

.include "io.s"

/*****************************************************************************/
/* Text segment                                                              */
/*****************************************************************************/

.text
        
.globl  _start
_start:
        /* Set up registers. */

        /* r0: Base address for PIOB. */
        lddpc r0, piob
        /* r1: Base address for PIOC. */
        lddpc r1, pioc
        /* r9: Counter for waitloop. */
        mov r9, 100000
        /* r10: Constantly 256. */
        mov r10, 256
        /* r11: Constantly 0xff. */
        mov r11, 0xff
        /* r12: Current LED setup. */
        mov r12, 1

        st.w r1[AVR32_PIO_PER], r11
        st.w r1[AVR32_PIO_OER], r11

step:
        st.w r1[AVR32_PIO_CODR], r11
        st.w r1[AVR32_PIO_SODR], r12

        mov r9, 100000

waitloop:
        sub r9, 1
        brne waitloop

        rol r12
        cp.w r12, r10
        
        brne step

        mov r12, 1
        rjmp step

piob: 
        .int AVR32_PIOB
pioc: 
        .int AVR32_PIOC

/*****************************************************************************/
/* Data segment                                                              */
/*****************************************************************************/

.data
