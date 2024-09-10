/* 
 * File:   bye00035_lab5_main_v001.c
 * Author: brock
 *
 * Created on March 23, 2023, 2:18 PM
 */

#include "xc.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * In this lab, your objective is to create a 
 * fully functional library for the 3.3V Small LCD display by SwitchScience.  
 * This library should consist of an initialization function, 
 * cursor location set function, and a string writing function.  
 * Together you will use these functions to create and animate a message on the LCD display.
 */



void pic24_init() {
    CLKDIVbits.RCDIV = 0;                   // set frequency to 16 MHz
    AD1PCFG = 0xffff;                       // set all pins digital
    TRISA = 0b1111111111111110;             // set RA0 to output
}

void delay_ms(int ms){
    while(ms-- > 0){
        asm("repeat #15998");
        asm("nop");
    }
}


/**
 * This function should implement the complete sequence of lcd_cmd() 
 * writes and delays needed to initialize the LCD.
 * Make sure the contrast is adjustable (by a global variable, argument, or compiler definition).
 */
void lcd_init(void) {
    I2C2BRG = 0x9D;                         // set to a clock frequency of 100 kHz
    IFS3bits.MI2C2IF = 0;                   // Clear interrupt flag
    I2C2CONbits.I2CEN = 1;                  // Enable I2C Mode
    
    delay_ms(40);
    
    lcd_cmd(0b00111000);                    // function set
    lcd_cmd(0b00111001);                    // function set, advance instruction mode
    lcd_cmd(0b00010100);                    // interval set
    lcd_cmd(0b01110000);                    // contrast Low
    lcd_cmd(0b01011110);                    
    lcd_cmd(0b01101100);                    // follower control

    delay_ms(200);
    
    lcd_cmd(0b00111000);                    // function set
    lcd_cmd(0b00001100);                    // Display on
    lcd_cmd(0b00000001);                    // Clear Display
    
    delay_ms(2);
}


/**
 * This function should take a single byte/char command and write it out the I2C bus.  
 * The complete packet should consist of a START bit, address with R/nW byte, 
 * control byte, command/data byte, and STOP bit.
 * @param Package
 */
void lcd_cmd(char Package) {
    // The MI2C2IF requires a software reset before every send. 
    // The MI2C2IF can be triggered by many different events, not just by the acknowledgement (refer to the family datasheet). 
    // Additionally, this is not the only bit that you can wait on. 
    // Make sure you check what triggers whatever bit you use and whether or not it requires a software reset.
    
    // Send START
    IFS3bits.MI2C2IF = 0;                   // Refer to note above
    I2C2CONbits.SEN = 1;                    // Initiate Start condition
    
    delay_ms(2);
    while (I2C2CONbits.SEN == 1);           // SEN will clear when Start Bit is complete
    
    // Send Address and Write Command
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;                   // 8-bits consisting of the slave address and the R/nW bit
    
    // Send high byte (always 0x00)
    delay_ms(2);

    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b00000000;                   // 8-bits consisting of control byte
    
    // Send Package
    delay_ms(2);
    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Package;                      // 8-bits consisting of the data byte
    
    // Send STOP
    delay_ms(2);
    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;                    // PEN will clear when Stop bit is complete
    while (I2C2CONbits.PEN == 1);
}


/**
 * This function should consist of a single lcd_cmd() statement with a 
 * masked and calculated command to set the Cursor to row y, column x.
 * @param x
 * @param y
 */
void lcd_setCursor(char x, char y)
{
    
}


/**
 * This is really only a test function to verify the LCD operation.  
 * It should consist of a single I2C packet (START, Address, control, data, STOP).  
 * Unlike the lcd_cmd() function it will have different values for RS and CO bit values.
 * @param Package
 */
void lcd_printChar(char Package) {
    
    IFS3bits.MI2C2IF = 0;                   // Refer to note above
    I2C2CONbits.SEN = 1;                    // Initiate Start condition
    
    delay_ms(2);
    while (I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;                   // 8-bits consisting of the slave address and the R/nW bit

    delay_ms(2);    
    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000;                   // 8-bits consisting of control byte /w RS=1
    
    delay_ms(2);
    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Package;                      // 8-bits consisting of the data byte
   
    delay_ms(2);
    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;                    // PEN will clear when Stop bit is complete
    while (I2C2CONbits.PEN == 1);
}


int main(int argc, char** argv) {
    pic24_init();                           // set clock to 16MHz and all pins digital
    lcd_init();                             // initialize the LCD screen for future use
    
    lcd_printChar('a');              // print the char 'a' to the screen
    //0b01000001
    while(1);
    return (0);
}

