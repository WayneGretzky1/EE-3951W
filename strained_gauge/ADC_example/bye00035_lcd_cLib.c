/* 
 * File:   bye00035_lab5_main_v001.c
 * Author: brock
 *
 * Created on March 23, 2023, 2:18 PM
 */

#include "xc.h"
#include <string.h>
#include "bye00035_lcd_cLib.h"


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
                        //                      Column
                              // 0      1     2     3     4     5     6     7
    int DDRAMaddress[2][8] = {{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07},       
                              {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47}};          // Row 0 (Top) Row 1 (Bottom)

    int setCursor = DDRAMaddress[(int) x][(int) y];
    setCursor = setCursor | 0b10000000;
    lcd_cmd(setCursor);                             // Cursor now placed
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
    

    while (I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;                   // 8-bits consisting of the slave address and the R/nW bit

  
    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000;                   // 8-bits consisting of control byte /w RS=1
    

    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Package;                      // 8-bits consisting of the data byte
   

    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;                    // PEN will clear when Stop bit is complete
    while (I2C2CONbits.PEN == 1);
}


/**
 * This function should take an arbitrary length string and send it to the LCD.  
 * This will require multiple command/data byte pairs with the RS and CO bits controlling when the packet ends. 
 * Don?t forget to finish the packet with a STOP bit.
 * @param s
 */
void lcd_printStr(const char s[])
{
//    lcd_setCursor(0,0);
    // The MI2C2IF requires a software reset before every send. 
    // The MI2C2IF can be triggered by many different events, not just by the acknowledgement (refer to the family datasheet). 
    // Additionally, this is not the only bit that you can wait on. 
    // Make sure you check what triggers whatever bit you use and whether or not it requires a software reset.
    
    // Send START
    IFS3bits.MI2C2IF = 0;                   // Refer to note above
    I2C2CONbits.SEN = 1;                    // Initiate Start condition
    

    while (I2C2CONbits.SEN == 1);           // SEN will clear when Start Bit is complete
    
    // Send Address and Write Command
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;                   // 8-bits consisting of the slave address and the R/nW bit
    

    int length = strlen(s);
    for (int i=0; i < length - 1; i++) {

            while (IFS3bits.MI2C2IF == 0);
            IFS3bits.MI2C2IF = 0;
            I2C2TRN = 0b11000000;                // Control byte (HIGH) another control byte will follow the data byte unless a STOP condition is received

            // Send Package

            while (IFS3bits.MI2C2IF == 0);
            IFS3bits.MI2C2IF = 0;
            I2C2TRN = s[i];                      // 8-bits consisting of the data byte

                   // 8-bits consisting of the data byte
        
    }

    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000;                // Control byte (LOW) last control byte to be sent. Only a stream of data bytes is allowed to follow. This stream may only be terminated by a STOP condition.

    // Send Package

    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = s[length - 1];   
    
    // Send STOP

    while (IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    I2C2CONbits.PEN = 1;                         // PEN will clear when Stop bit is complete
    while (I2C2CONbits.PEN == 1);
}


void shiftRight()
{
    lcd_cmd(0b00011100);
}


void shiftLeft()
{
    lcd_cmd(0b00011000);
}


