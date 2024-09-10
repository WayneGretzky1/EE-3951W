/* 
 * File:   bye00035_lab6_main_v001.c
 * Author: bye00035
 *
 * Created on April 7, 2023, 11:24 AM
 */

#include "xc.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bye00035_circularBuffer_v001.h"
#include "bye00035_adc_v001.h"
#include "bye00035_lcd_cLib.h"

///////////////////////////////START BOILERPLATE///////////////////////////////
#include <p24FJ64GA002.h>
#include "xc.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)
// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
///////////////////////////////END BOILERPLATE/////////////////////////////////

/*
 * 
 */

void pic24_init() {
    CLKDIVbits.RCDIV = 0;                   // set frequency to 16 MHz
    AD1PCFG = 0xffff;                       // set all pins digital
}



void __attribute__ ((__interrupt__)) _ADC1Interrupt(void)
{
    IFS0bits.AD1IF = 0;     // Reset Interrupt Flag
    putVal(ADC1BUF0);
    
}


void __attribute__ ((__interrupt__)) _T1Interrupt()
{
    IFS0bits.T1IF = 0;      // Reset Interrupt Flag
    
    unsigned int adValue;
    char adStr[20];
    adValue = (double) getAvg();
    sprintf(adStr, "%6.4f V", (3.3/1024)* (double) adValue);  // ?x.xxxx V?
//                       // 6.4 in the format string ?%6.4f? means 6 placeholders for the whole
//                       // floating-point number, 4 of which are for the fractional part.
//            lcd_printStr((const char *) sprintf(adStr, "%6.4f V", (3.3/1024)*adValue));

    lcd_printStr(adStr);    // Print current getAvg to LCD Display
    lcd_setCursor(1,0);
    lcd_printStr("A/D");
    lcd_setCursor(0,0);
}




int main(int argc, char** argv) {
    pic24_init();
    lcd_init();
    adc_init();
    timer1_init();
    initBuffer();
    
    while (1) {}
    
    return (EXIT_SUCCESS);
}

