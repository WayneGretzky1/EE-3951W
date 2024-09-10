/* 
 * File:   lcd_display.h
 * Author: lunab
 *
 * Created on November 9, 2023, 2:27 PM
 */

#ifndef LCD_DISPLAY_H
#define	LCD_DISPLAY_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif

void lcd_init(void);
void lcd_cmd(char command);
void lcd_setCursor(char x, char y);
void lcd_printChar(char myChar);
void lcd_printStr(const char s[]);


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_DISPLAY_H */

