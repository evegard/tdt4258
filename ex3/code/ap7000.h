/* PIO macros and types for AT32AP7000 */
/* taken from Atmel's IO headers */

#ifndef AP7000PIO_H
#define AP7000PIO_H

/* PIOA */ 
#define AVR32_PIOA_ADDRESS                 0xFFE02800
#define AVR32_PIOA                         (*((volatile avr32_pio_t*)AVR32_PIOA_ADDRESS))
#define AVR32_PIOA_IRQ                     416
#define AVR32_PIOA_PIOA_LINES              32


/* PIOB */ 
#define AVR32_PIOB_ADDRESS                 0xFFE02C00
#define AVR32_PIOB                         (*((volatile avr32_pio_t*)AVR32_PIOB_ADDRESS))
#define AVR32_PIOB_IRQ                     448
#define AVR32_PIOB_PIOB_LINES              31


/* PIOC */ 
#define AVR32_PIOC_ADDRESS                 0xFFE03000
#define AVR32_PIOC                         (*((volatile avr32_pio_t*)AVR32_PIOC_ADDRESS))
#define AVR32_PIOC_IRQ                     480
#define AVR32_PIOC_PIOC_LINES              32


/* PIOD */ 
#define AVR32_PIOD_ADDRESS                 0xFFE03400
#define AVR32_PIOD                         (*((volatile avr32_pio_t*)AVR32_PIOD_ADDRESS))
#define AVR32_PIOD_IRQ                     512
#define AVR32_PIOD_PIOD_LINES              19


/* PIOE */ 
#define AVR32_PIOE_ADDRESS                 0xFFE03800
#define AVR32_PIOE                         (*((volatile avr32_pio_t*)AVR32_PIOE_ADDRESS))
#define AVR32_PIOE_IRQ                     544
#define AVR32_PIOE_PIOE_LINES              27

#define AVR32_PIO_ABSR 0x00000078
#define AVR32_PIO_ASR  0x00000070
#define AVR32_PIO_BSR  0x00000074
#define AVR32_PIO_CODR 0x00000034
#define AVR32_PIO_IDR  0x00000044
#define AVR32_PIO_IER  0x00000040
#define AVR32_PIO_IFDR 0x00000024
#define AVR32_PIO_IFER 0x00000020
#define AVR32_PIO_IMR  0x00000048
#define AVR32_PIO_ISFR 0x00000028
#define AVR32_PIO_ISR  0x0000004c
#define AVR32_PIO_MDDR 0x00000054
#define AVR32_PIO_MDER 0x00000050
#define AVR32_PIO_MDSR 0x00000058
#define AVR32_PIO_ODR  0x00000014
#define AVR32_PIO_ODSR 0x00000038
#define AVR32_PIO_OER  0x00000010
#define AVR32_PIO_OSR  0x00000018
#define AVR32_PIO_OWDR 0x000000a4
#define AVR32_PIO_OWER 0x000000a0
#define AVR32_PIO_OWSR 0x000000a8
#define AVR32_PIO_PDR  0x00000004
#define AVR32_PIO_PDSR 0x0000003c
#define AVR32_PIO_PER  0x00000000
#define AVR32_PIO_PSR  0x00000008
#define AVR32_PIO_PUDR 0x00000060
#define AVR32_PIO_PUER 0x00000064
#define AVR32_PIO_PUSR 0x00000068
#define AVR32_PIO_SODR 0x00000030

typedef struct avr32_pio_per_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_per_t;



typedef struct avr32_pio_pdr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_pdr_t;



typedef struct avr32_pio_psr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_psr_t;



typedef struct avr32_pio_oer_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_oer_t;



typedef struct avr32_pio_odr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_odr_t;



typedef struct avr32_pio_osr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_osr_t;



typedef struct avr32_pio_ifer_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_ifer_t;



typedef struct avr32_pio_ifdr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_ifdr_t;



typedef struct avr32_pio_isfr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_isfr_t;



typedef struct avr32_pio_sodr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_sodr_t;



typedef struct avr32_pio_codr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_codr_t;



typedef struct avr32_pio_odsr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_odsr_t;



typedef struct avr32_pio_pdsr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_pdsr_t;



typedef struct avr32_pio_ier_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_ier_t;



typedef struct avr32_pio_idr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_idr_t;



typedef struct avr32_pio_imr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_imr_t;



typedef struct avr32_pio_isr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_isr_t;



typedef struct avr32_pio_mder_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_mder_t;



typedef struct avr32_pio_mddr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_mddr_t;



typedef struct avr32_pio_mdsr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_mdsr_t;



typedef struct avr32_pio_pudr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_pudr_t;



typedef struct avr32_pio_puer_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_puer_t;



typedef struct avr32_pio_pusr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_pusr_t;



typedef struct avr32_pio_asr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_asr_t;



typedef struct avr32_pio_bsr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_bsr_t;



typedef struct avr32_pio_absr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_absr_t;



typedef struct avr32_pio_ower_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_ower_t;



typedef struct avr32_pio_owdr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_owdr_t;



typedef struct avr32_pio_owsr_t {
    unsigned int p31             : 1;
    unsigned int p30             : 1;
    unsigned int p29             : 1;
    unsigned int p28             : 1;
    unsigned int p27             : 1;
    unsigned int p26             : 1;
    unsigned int p25             : 1;
    unsigned int p24             : 1;
    unsigned int p23             : 1;
    unsigned int p22             : 1;
    unsigned int p21             : 1;
    unsigned int p20             : 1;
    unsigned int p19             : 1;
    unsigned int p18             : 1;
    unsigned int p17             : 1;
    unsigned int p16             : 1;
    unsigned int p15             : 1;
    unsigned int p14             : 1;
    unsigned int p13             : 1;
    unsigned int p12             : 1;
    unsigned int p11             : 1;
    unsigned int p10             : 1;
    unsigned int p9              : 1;
    unsigned int p8              : 1;
    unsigned int p7              : 1;
    unsigned int p6              : 1;
    unsigned int p5              : 1;
    unsigned int p4              : 1;
    unsigned int p3              : 1;
    unsigned int p2              : 1;
    unsigned int p1              : 1;
    unsigned int p0              : 1;
} avr32_pio_owsr_t;



typedef struct avr32_pio_t {
  union {
          unsigned long                  per       ;//0x0000
          avr32_pio_per_t                PER       ;
  };
  union {
          unsigned long                  pdr       ;//0x0004
          avr32_pio_pdr_t                PDR       ;
  };
  union {
    const unsigned long                  psr       ;//0x0008
    const avr32_pio_psr_t                PSR       ;
  };
          unsigned int                   :32       ;//0x000c
  union {
          unsigned long                  oer       ;//0x0010
          avr32_pio_oer_t                OER       ;
  };
  union {
          unsigned long                  odr       ;//0x0014
          avr32_pio_odr_t                ODR       ;
  };
  union {
    const unsigned long                  osr       ;//0x0018
    const avr32_pio_osr_t                OSR       ;
  };
          unsigned int                   :32       ;//0x001c
  union {
          unsigned long                  ifer      ;//0x0020
          avr32_pio_ifer_t               IFER      ;
  };
  union {
          unsigned long                  ifdr      ;//0x0024
          avr32_pio_ifdr_t               IFDR      ;
  };
  union {
    const unsigned long                  isfr      ;//0x0028
    const avr32_pio_isfr_t               ISFR      ;
  };
          unsigned int                   :32       ;//0x002c
  union {
          unsigned long                  sodr      ;//0x0030
          avr32_pio_sodr_t               SODR      ;
  };
  union {
          unsigned long                  codr      ;//0x0034
          avr32_pio_codr_t               CODR      ;
  };
  union {
          unsigned long                  odsr      ;//0x0038
          avr32_pio_odsr_t               ODSR      ;
  };
  union {
    const unsigned long                  pdsr      ;//0x003c
    const avr32_pio_pdsr_t               PDSR      ;
  };
  union {
          unsigned long                  ier       ;//0x0040
          avr32_pio_ier_t                IER       ;
  };
  union {
          unsigned long                  idr       ;//0x0044
          avr32_pio_idr_t                IDR       ;
  };
  union {
    const unsigned long                  imr       ;//0x0048
    const avr32_pio_imr_t                IMR       ;
  };
  union {
    const unsigned long                  isr       ;//0x004c
    const avr32_pio_isr_t                ISR       ;
  };
  union {
          unsigned long                  mder      ;//0x0050
          avr32_pio_mder_t               MDER      ;
  };
  union {
          unsigned long                  mddr      ;//0x0054
          avr32_pio_mddr_t               MDDR      ;
  };
  union {
    const unsigned long                  mdsr      ;//0x0058
    const avr32_pio_mdsr_t               MDSR      ;
  };
          unsigned int                   :32       ;//0x005c
  union {
          unsigned long                  pudr      ;//0x0060
          avr32_pio_pudr_t               PUDR      ;
  };
  union {
          unsigned long                  puer      ;//0x0064
          avr32_pio_puer_t               PUER      ;
  };
  union {
    const unsigned long                  pusr      ;//0x0068
    const avr32_pio_pusr_t               PUSR      ;
  };
          unsigned int                   :32       ;//0x006c
  union {
          unsigned long                  asr       ;//0x0070
          avr32_pio_asr_t                ASR       ;
  };
  union {
          unsigned long                  bsr       ;//0x0074
          avr32_pio_bsr_t                BSR       ;
  };
  union {
    const unsigned long                  absr      ;//0x0078
    const avr32_pio_absr_t               ABSR      ;
  };
          unsigned int                   :32       ;//0x007c
          unsigned int                   :32       ;//0x0080
          unsigned int                   :32       ;//0x0084
          unsigned int                   :32       ;//0x0088
          unsigned int                   :32       ;//0x008c
          unsigned int                   :32       ;//0x0090
          unsigned int                   :32       ;//0x0094
          unsigned int                   :32       ;//0x0098
          unsigned int                   :32       ;//0x009c
  union {
          unsigned long                  ower      ;//0x00a0
          avr32_pio_ower_t               OWER      ;
  };
  union {
          unsigned long                  owdr      ;//0x00a4
          avr32_pio_owdr_t               OWDR      ;
  };
  union {
    const unsigned long                  owsr      ;//0x00a8
    const avr32_pio_owsr_t               OWSR      ;
  };
} avr32_pio_t;

#endif
