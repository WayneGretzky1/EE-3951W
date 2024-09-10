#include "xc.h"
#include "randa444_lab4_button_v001.h"

void initButton()
{
    TRISBbits.TRISB8 = 1;
    CNPU2bits.CN22PUE = 1;
    
    T2CON = 0;
    T2CONbits.TCKPS = 0b11;
    TMR2 = 0;
    PR2 = 62499;  //1 second
    
    _T2IE = 1;
    _T2IF = 0;
    
    T2CONbits.TON = 1;
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 8;  // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    IC1CON = 1; // Turn off and reset internal state of IC1
    IC1CONbits.ICTMR = 1; // Use Timer 2 for capture source
    IC1CONbits.ICM = 0b011; // Turn on and capture every rising edge
    _IC1IF = 0;
    _IC1IE = 1;
}
