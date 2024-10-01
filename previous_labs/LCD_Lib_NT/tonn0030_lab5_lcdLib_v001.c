/*
 * File:   tonn0030_lab5_lcdlib_v001.c
 * Author: Nathan Tonn - tonn0030
 *
 * Created on March 18, 2024, 12:48 AM
 */
#include "xc.h"
#include "tonn0030_lab5_lcdLib_v001.h"

/**
 * A function that moves the position of the LCD cursor to the specified location. 
 * @param row Which of the two rows to move to. 0 or 1
 * @param column Which of the eight columns. 0-7
 */
void lcd_moveCurser(char row, char column)
{
    char package = 0x80 | (0x40 * row + column);
    lcd_cmd(package);
}

/**
 * lcd_clear is just a function that calls the I2C clear command, I just wrapped
 * it in a function to make it look better.
 */
void lcd_clear(void)
{
    lcd_cmd(0b00000001);
}

/**
 * The printChar function takes in a character and writes it to the current
 * cursor location. This also automatically moves the cursor one position right.
 * @param Package The character to be written.
 */
void lcd_printChar(char Package)
{
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = SLAVE_ADDR;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Package;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
}

/**
 * This function takes in a null-terminated string and prints all the characters
 * to the LCD in a row. If the string is longer than 8 characters, the LCD will 
 * not show the whole thing.
 * @param str The null terminated character array to be printed.
 */
void lcd_printStr(const char str[])
{
    int i;
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = SLAVE_ADDR;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    for(i = 0; str[i+1] != '\0'; i++)
    {
        I2C2TRN = 0b11000000;
        while(IFS3bits.MI2C2IF == 0);
        IFS3bits.MI2C2IF = 0;
        I2C2TRN = str[i];
        while(IFS3bits.MI2C2IF == 0);
        IFS3bits.MI2C2IF = 0;
    }
    I2C2TRN = 0b01000000;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = str[i];
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
}

/**
 * The lcd_cmd function can take any 8bit I2C write instruction and write it to
 * the lcd. This function utilizes the I2C2 peripheral.
 * @param Package The 8bit package to be written to the I2C line after overhead.
 */
void lcd_cmd(char Package)
{
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = SLAVE_ADDR;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b00000000;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = Package;
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
}

/**
 * A configuration function that initializes the lcd screen's options, turns it
 * on, and clears it.
 */
void lcd_config(void)
{
    delayMs(50);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000); // contrast C3-C0
    lcd_cmd(0b01011110); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
    delayMs(200);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    delayMs(2);
}

/**
 * lcd_init enables the I2C2 peripheral's baud rate and enables it, then calls
 * the @ref lcd_config function.
 */
void lcd_init(void)
{
    I2C2BRG = 157;
    I2C2CONbits.I2CEN = 1;
    lcd_config();
}