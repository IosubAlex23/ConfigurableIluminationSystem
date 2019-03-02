/*
 * LCD_Driver.h
 *
 *  Created on: 9 mai 2018
 *      Author: Alex
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "types.h"
#include "GPIO_module.h"

void LCD_Command(uint8 cmnd);
void LCD_Char(uint8 data);
void LCD_Char_xy(uint8 row, uint8 pos, uint8 *str);
void LCD_Init(void);
void LCD_String(uint8 *str);
void LCD_String_xy(uint8 row, uint8 pos, uint8 *str);
void LCD_Clear();

#endif /* LCD_DRIVER_H_ */
