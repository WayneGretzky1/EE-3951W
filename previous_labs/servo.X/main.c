/*
 * File:   main.c
 * Author: brock
 *
 * Created on November 12, 2024, 10:01 AM
 */


#include "xc.h"
#include "servo_setup.h"

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
Function: basicSetup
---------------------------------------
Simply sets the PIC24 internal clock to 16MHz, and assigns all pins to digital.
 */
void basicSetup(void){
    ////PIC24 basic setup
    CLKDIVbits.RCDIV = 0;   //Set RCDIV as 1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0xffff;       //set all pins digital
}
//void setup() {
//    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
//    TRISA = 0b0000000000011111;  //set port A to inputs, 
//    TRISB = 0b0000000000000011;  //and port B to outputs
//    LATA = 0xffff;               //Set all of port A to HIGH
//    LATB = 0xffff;               //and all of port B to HIGH
//}

int main(void) {
//    setup();
    

    basicSetup();
    servoSetup(); // 1000-5000
    
    while(1){
        setScaleServo(0);
        for(int i = 0; i<400; i++){
            nat_delay1ms();
        }
        for(int i = 0; i<1023; i += 10){
            setScaleServo(i);
            for(int i = 0; i<30; i++){
                nat_delay1ms();
            }
        }
//        LATB = LATB & 0x7FFF;
    }
    return 0;
}
