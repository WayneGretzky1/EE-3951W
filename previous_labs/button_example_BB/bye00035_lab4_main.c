#include "xc.h"

#pragma config ICS = PGx1       // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF     // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF       // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF        // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF     // JTAG Port Enable (JTAG port is disabled)
// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI    // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF    // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON    // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME   // Clock Switching and Monitor (Clock switching is enabled,
                                    // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL   // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

volatile int T2rollover = 0;
void delay_ms(int ms){
    while(ms-- > 0){
        asm("repeat #15998");
        asm("nop");
    }
}


void initServo(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISBbits.TRISB6 = 0;                       // Set RB6 to output
    
    //map output compare to RB6
    __builtin_write_OSCCONL(OSCCON & 0xbf);     // Unlock PPS
//    RPINR7bits.IC1R = 8;                      // Use Pin RP8 = "8", for Input Capture 1 (Table 10-2)
    RPOR3bits.RP6R = 18;                        // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40);     // Lock PPS
    
    //setup timer 3
    T3CON = 0;    
    T3CONbits.TCKPS = 1;
    PR3 = 39999;
    
    // Output compare peripheral
    OC1CON = 0;                                 // Turn off OC1 for now
    OC1R = 1234;                                // Servo start position. We won't touch OC1R again
    OC1RS = 1234;                               // We will only change this once the PWM is turned on
    OC1CONbits.OCTSEL = 1;                      // Use Timer 3 for compare source
    OC1CONbits.OCM = 0b110;                     // Output compare PWM w/o faults
    T3CONbits.TON = 1;                          // Enable TImer 3
}


void setServo(int Val){
    // Sets servo to a specific angle 
    // Range between 0-PR3
    OC1RS = Val;                                // PR3 * (Val/100);
}


void initPushButton(void){
    TRISBbits.TRISB8 = 1;
    CNPU2bits.CN22PUE= 1;
    T2CON = 0;
    T2CONbits.TCKPS = 0b11;
    PR2 = 62499;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;
}


void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(){
    _T2IF = 0;
    T2rollover += 1;
}


int main(void){
    initServo();
    while (1) {
        delay_ms(2000);
        setServo(10000);
        delay_ms(2000);
        setServo(30000);
    }
    return 0;
}

