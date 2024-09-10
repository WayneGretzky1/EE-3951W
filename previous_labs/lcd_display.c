#include "xc.h"
#include "lcd_display.h"

void lcd_init(void);
void lcd_cmd(char command);
void lcd_setCursor(char x, char y);
void lcd_printChar(char myChar);
void lcd_printStr(const char s[]);

lcd_init(void)          //initialize the lcd display
{
    I2C2BRG = 0x009D;   //baud rate of 157
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;
    
    delay(40);
    
    lcd_cmd(0b00111000); //function set
    lcd_cmd(0b00111001); //function set, advance instruction mode
    lcd_cmd(0b00010100); //interval osc
    lcd_cmd(0b01110000); //contrast low
    lcd_cmd(0b01010110);
    lcd_cmd(0b01101100); //follower control
    
    delay(200);
    
    lcd_cmd(0b00111000); //function set
    lcd_cmd(0b00001100); //display on
    lcd_cmd(0b00000001); //clear display
    
    delay(1);
}

void lcd_cmd(char command) //send package to lcd display
{
    //send start
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    
    //send address and write command
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    //send high byte (always 0x00)
    I2C2TRN = 0b00000000; // 8-bits consisting of control byte
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    //send package
    I2C2TRN = command;
    while(IFS3bits.MI2C2IF == 0);
    
    //send stop
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
}

lcd_setCursor(char x, char y)  //set the cursor of the lcd display to the (x,y) location
{
    int cursor = ((0x40 * x) + y) | 0b10000000;
    lcd_cmd(cursor);
}

lcd_printChar(char myChar)  //print a character to the display
{
    //send start
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0;
    
    //send address and write command
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    //send high byte (always 0x00)
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    
    //send package
    I2C2TRN = myChar;
    while(IFS3bits.MI2C2IF == 0);
    
    //send stop
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1);
}

lcd_printStr(const char str[])  //print a string on the lcd display
{
    int len = strlen(str);
    for(int i = 0; i <= len; i++)
    {
        lcd_printChar(str[i]);
    }
}
