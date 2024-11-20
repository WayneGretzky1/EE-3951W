/*
 * File:   servo_setup.c
 * Author: brock
 *
 * Created on November 12, 2024, 10:05 AM
 */


#include <p24FJ64GA002.h>
#include "xc.h"
#include "servo_setup.h"


/*
 Function: servoSetup
 -------------------------------
 Sets pins 26,25,24,23,22 as Output Compare 1,2,3,4,5 respectively, which send
 * out a defined Pulse Width of 20 miliseconds. Timer 3 is also set up to be
 * used for the OC, with a Pre-scalar of 1:8 and set its Period to the 20 ms
 * value (39999). 
 */
void servoSetup(void){                      //Servo basic setup
    
    //Pin assignment begin
    TRISBbits.TRISB6 = 0;                  //Pin 15 (RB6) is output
    
    //Setup the Peripheral Pin Select
    __builtin_write_OSCCONL(OSCCON & 0xBF); //Unlocks the PPS for OC selection
    RPOR3bits.RP6R = 18;                   //Set RP6 as OC-1
    __builtin_write_OSCCONL(OSCCON & 0x40); //Re-locks the PPS
    
    
    
    //Setup Timer 2 for Output Compare
    
    T2CON = 0;                  //Stop timer and resets control register
    T2CONbits.TCKPS = 0b01;     //Pre-Scalar. 0b01 = 1:8 pre-scale (PG. 14-6)
    TMR2 = 0;                   //Clear contents of timer register
    PR2 = 40000 - 1;            //Period register. Period is = PRx_value + 1
                                //40000 cycles at 1:8 makes a 20 mil sec period
    T2CONbits.TON = 1;
    
    
    
    //Output Compare 1 setup
    
    OC1CON = 0;                 //Turn off OC-1 for now
    OC1R = 3000;                //Servo start position at 90 degrees
    OC1RS = 3000;               //The next value to be written to the OC1R
    OC1CONbits.OCTSEL = 0b00;   //Use Timer 2 for compare source
    OC1CONbits.OCM = 0b110;     //OC-1 mode is PWM without faults
    
//    OC1CONbits= 1;


}

/*
Function: setServo
---------------------------------------
Updates the OC1RS register with Val. Val is an integer from 0 to PR3 (39999).
    40,000 counts is 20 ms, so there is a 20 ms pulse width. Val can be
    computed as Val = (desired_num_ms_HIGH)*2000. This is because 40,000 counts
    in 20 ms, so 2000 counts/ms.
 * servo: an integer value from 1 to 5, selecting OC 1-5 respectively
 * val: cycles of the PWM duty cycle which are set as high
 */
void setServo(int val){
    OC1RS = val;
}

void setScaleServo(int weight){
    setServo((int)(-4000*(weight/1024.0)+5000));
}
