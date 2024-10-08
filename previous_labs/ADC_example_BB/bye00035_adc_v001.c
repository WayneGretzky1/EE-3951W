
#include <p24FJ64GA002.h>
#include "bye00035_adc_v001.h"

void adc_init()
{
    //TRISAbits.TRISA0 = 1;
    TRISBbits.TRISB2 = 1;               // should be input by default
    AD1CHS &= 0xFFF0;
    AD1CHS |= 0x0004;
    //AD1PCFGbits.PCFG0 = 0;
    AD1PCFGbits.PCFG4 = 0;              // setup I/o as analog
    
    //AD1CON2bits.VCFG = 0b000;           // Use AVDD (3.3V) and AVSS (0V) as max/min
    AD1CON2bits.VCFG = 0b011;           //VREF-,VREF+
    AD1CON3bits.ADCS = 0b011;           // You want TAD >= 75ns(Tcy = 62.5ns) (Currently A/D conversion clock as 3Tcy)
    AD1CON1bits.SSRC = 0b010;           // Sample on timer3 events (timer3 compare match)
    AD1CON3bits.SAMC = 0b00001;         // You want at least 1 auto sample time bit (currently assigned 1 auto sample)
    AD1CON1bits.FORM = 0b00;            // Data output form (unsigned int) -- recommended unsigned int 

    // unsigned: 0V = 0b0000000000, 3.3V = 0b1111111111
    // signed:   0V = 0b1000000000, 3.3V = 0b0011111111

    // TAD (A/D clock cycle) = TCY(ADCS + 1)
    // ADCS (A/D Conversion Clock Period Select bits) = (TAD/Tcy) - 1
    
    AD1CON1bits.ASAM = 1;               // Sampling begins immediately after last conversion completes; SAMP bit is automatically set
    AD1CON2bits.SMPI = 0b0000;          // Interrupts at the completion of conversion for each 16th sample/convert sequence 
    AD1CON1bits.ADON = 1;               // Turn on the ADC

    _AD1IF = 0;                         // Clear Interrupt Flag
    _AD1IE = 1;                         // Enable Interrupt

    TMR3 = 0;                           // Setup timer3
    T3CON = 0;                          // Clear timer3 register
    T3CONbits.TCKPS = 0b00;             // Pre-scaler (1:1)
    PR3 = 62499;                        // Clk period (3.91ms, sampling 256 times per second)
    T3CONbits.TON = 1;                  // Start timer3
}


void timer1_init()
{
    TMR1 = 0;                           // Setup timer1
    T1CON = 0;                          // Clear timer1 register
    T1CONbits.TCKPS = 0b10;             // Pre-scaler (1:64)
    PR1 = 24999;                        // Clk period (100ms)
    T1CONbits.TON = 1;                  // Start timer1
    
    _T1IF = 0;                          // Clear Interrupt Flag
    _T1IE = 1;                          // Enable Interrupt
}
