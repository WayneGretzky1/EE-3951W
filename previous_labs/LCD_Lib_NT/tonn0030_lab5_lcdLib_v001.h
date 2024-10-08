/* 
 * File:   tonn0030_lab5_lcdLib_v001.h
 * Author: ntonn
 *
 * Created on March 15, 2024, 10:55 PM
 */

#include "xc.h"

#ifndef TONN0030_LAB4_LCDLIB_H
#define	TONN0030_LAB4_LCDLIB_H

#define SLAVE_ADDR 0b01111100

#ifdef	__cplusplus
extern "C" {
#endif

void lcd_cmd(char Package);
void lcd_clear(void);
void lcd_init(void);
void lcd_moveCurser(char row, char column);
void lcd_printChar(char Package);
void lcd_printStr(const char str[]);
void delayMs(int ms);
#ifdef	__cplusplus
}
#endif

#endif

