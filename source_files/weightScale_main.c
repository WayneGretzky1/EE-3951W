/* 
 * File:   bye00035_lab5_main_v001.c
 * Author: brock
 *
 * Created on March 23, 2023, 2:18 PM
 */

#include "xc.h"
#include "../previous_labs/ADC_example_BB/bye00035_adc_v001.h"
#include "../previous_labs/buffer_lib_NT/tonn0030_lab6_bufferLib_v001.h"
#include "../previous_labs/LCD_Lib_NT/tonn0030_lab5_lcdLib_v001.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

/*
 * In this lab, your objective is to create a 
 * fully functional library for the 3.3V Small LCD display by SwitchScience.  
 * This library should consist of an initialization function, 
 * cursor location set function, and a string writing function.  
 * Together you will use these functions to create and animate a message on the LCD display.
 */

volatile int test;
volatile char time_to_refresh = 0;


void __attribute__((interrupt, auto_psv)) _ADC1Interrupt()
{
    _AD1IF = 0;
    putVal(ADC1BUF0);
    time_to_refresh += 1;
}


void setup()
{
    initBuffer(4);
    adc_init();
    lcd_init();
    lcd_moveCurser(0,0);
    TMR3 = 0;
    T3CON = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 31250 - 1;
    T3CONbits.TON = 1;
}

// use shift left command for part 2
int main(int argc, char** argv) {
    char adStr[20];
    setup();
    int adValue = getAvg();
    while(1){
        if(time_to_refresh >= 4){
            adValue = getAvg();
            sprintf(adStr, "%d", adValue);
            lcd_clear();            
            delayMs(2);
            lcd_moveCurser(0,0);
            lcd_printStr(adStr);
            time_to_refresh = 0;
        }
    }

    return (0);
}

