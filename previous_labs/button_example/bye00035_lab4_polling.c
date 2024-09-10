/*
 * File:   borha008_23_lab4_main_v001.c
 * Author: Jake
 *
 * Created on March 2, 2023, 11:44 AM
 */


#include "xc.h"
#include <assert.h> 
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
volatile uint32_t last_time = 0;
volatile uint32_t last_last_time = 0;
volatile int PrevState = 1;
volatile uint32_t time_set = 0;

#define BUFFER_SIZE 3  //2 for double,  3 for triple
volatile int Idex = 0;
volatile uint32_t buffer[BUFFER_SIZE];


void delay_ms(int ms){
    while(ms-- > 0){
        asm("repeat #15998");
        asm("nop");
    }
}

//rb6 output, out
void initServo(void){
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISBbits.TRISB6 = 0;
    //map output compare to rb6
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
//    RPINR7bits.IC1R = 8;  // Use Pin RP8 = "8", for Input Capture 1 (Table 10-2)
    RPOR3bits.RP6R = 18;  // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    //setup timer 3
    T3CON = 0;
    
    T3CONbits.TCKPS = 1;
    PR3 = 39999;
    
    //output compare periferal
    OC1CON = 0;    // turn off OC1 for now
    OC1R = 2000;   // servo start position. We won?t touch OC1R again
    OC1RS = 2000;  // We will only change this once PWM is turned on
    OC1CONbits.OCTSEL = 1; // Use Timer 3 for compare source
    OC1CONbits.OCM = 0b110; // Output compare PWM w/o faults
    T3CONbits.TON = 1;
    

}

void setServo(int Val){
    //sets servo to angle 
    //range between 0-PR3
    OC1RS = Val;//PR3 * (Val/100);
}

void initPushButton(void){
    TRISBbits.TRISB8 = 1;
    CNPU2bits.CN22PUE= 1;
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 8;  // Use Pin RP8 = "8", for Input Capture 1 (Table 10-2)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    T2CON = 0;
    T2CONbits.TCKPS = 0b11;
    PR2 = 62499;
    _T2IF = 0;
    _T2IE = 1;
    T2CONbits.TON = 1;
    IC1CON = 0; // every edge
    IC1CONbits.ICM = 2;
    IC1CONbits.ICTMR = 1;
    _IC1IF = 0;
    _IC1IE = 1;

    
}

void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(){
    _T2IF = 0;
    T2rollover += 1;
    
}

void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt(void)
{
    
    _IC1IF = 0;
     uint32_t current_time = (uint32_t)(PR2) * (T2rollover) + IC1BUF; 
    if((current_time - last_time) > 13){
        //last_time = current_time;//debounce
        if(PrevState == 1){
            PrevState -=1;
            

            if(((current_time - last_time) < 15625) && ((last_time - last_last_time) < 15625)){
                time_set = current_time;
                setServo(4000);
            }
            
        }
        else{
            PrevState = 1;
        }
        last_last_time = last_time;
        last_time = current_time;//debounce
        
    }
}

int main(void) {
    initServo();
    initPushButton();
    uint32_t prev_time;
    uint32_t curr_time;
    uint32_t prev_prev_time;
     setServo(2000);
     int prev_index = 0;
    while(1){

        if((((uint32_t)PR2*T2rollover + TMR2) - time_set) > 125000){
          setServo(2000);  
        }
    }
    return 0;
}
