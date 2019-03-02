/*
 * DDrvButton.h
 *
 *  Created on: 19 mai 2018
 *      Author: Alex
 */

#ifndef DDRVBUTTON_H_
#define DDRVBUTTON_H_

#include <derivative.h>
#include "types.h"
#include "delay.h"
#include "GPIO_module.h"

typedef enum {
	Button_NotPressed=0,
	Button_Pressed=1,
} Button_State;

void ButtonInit(uint8 btnPin);
Button_State isGPIOA_ButtonPressed(uint8 btnPin);

#endif /* DDRVBUTTON_H_ */
