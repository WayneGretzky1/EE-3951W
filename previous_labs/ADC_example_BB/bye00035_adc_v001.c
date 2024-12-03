
#include <p24FJ64GA002.h>
#include "bye00035_adc_v001.h"

void adc_init()
{
    AD1PCFG = 0xFFDF; // Only AN4 as analog input
    AD1CON1 = 0x00E0; // Internal counter triggers conversion
    //AD1CHS = 0x0000; // Connect AN0 as positive input
    AD1CHS &= 0x0000;
    AD1CHS |= 0b0101;  // Connect AN4 as positive input
    AD1CSSL = 0;
    AD1CON3 = 0x0F3F; // Sample time = 15Tad, Tad = Tcy
    AD1CON2 = 0x601C; // Set AD1IF after every 8 samples, Vrefs enabled 657, 313
    //AD1CON2 = 0x001C; // Set AD1IF after every 8 samples, Vcc and gnd
    AD1CON1bits.ADON = 1; // turn ADC ON
    IFS0bits.AD1IF = 0; // clear ADC interrupt flag
    _AD1IE = 1;
    AD1CON1bits.ASAM = 1; // auto start sampling for 31Tad
}