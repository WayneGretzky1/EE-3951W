/* 
 * File:   bye00035_lab5_cLib.h
 * Author: bye00035
 *
 * Created on April 4, 2023, 4:13 PM
 */

#ifndef BYE00035_LCD_CLIB_H
#define	BYE00035_LCD_CLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

    void delay_ms(int ms);
    void lcd_init(void);
    void lcd_cmd(char Package);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char Package);
    void lcd_printStr(const char s[]);
    void shiftRight();
    void shiftLeft();

#ifdef	__cplusplus
}
#endif

#endif	/* BYE00035_LCD_CLIB_H */

