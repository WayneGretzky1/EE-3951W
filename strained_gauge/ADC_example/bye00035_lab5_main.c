/* 
 * File:   bye00035_lab5_main_v001.c
 * Author: brock
 *
 * Created on March 23, 2023, 2:18 PM
 */

#include "xc.h"
#include "bye00035_lab5_cLib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * In this lab, your objective is to create a 
 * fully functional library for the 3.3V Small LCD display by SwitchScience.  
 * This library should consist of an initialization function, 
 * cursor location set function, and a string writing function.  
 * Together you will use these functions to create and animate a message on the LCD display.
 */




// use shift left command for part 2
int main(int argc, char** argv) {
    
    pic24_init();                                // set clock to 16MHz and all pins digital
    lcd_init();                                  // initialize the LCD screen for future use
    

    const char myString[] = "Hello World!";
    for (int i=0; i < 32; i++) {
        lcd_printStr(myString);
        shiftRight();
        delay_ms(50);
    }
        lcd_cmd(0b00000001);                    // Clear Display
//    lcd_setCursor(1,0);
    for (int i=0; i < 32; i++) {
        lcd_printStr(myString);
        shiftRight();
        delay_ms(50);
    }
            lcd_cmd(0b00000001);                    // Clear Display
    while(1);

    return (0);
}

