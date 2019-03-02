/*
 * DDrvJoystick.h
 *
 *  Created on: 12 mai 2018
 *      Author: Alex
 */

#ifndef DDRVJOYSTICK_H_
#define DDRVJOYSTICK_H_

#include "types.h"

typedef enum {
	JoyStick_Center=0,
	JoyStick_North,
	JoyStick_South,
	JoyStick_East,
	JoyStick_West
} Joystick_State;


void JoyStick_Init(uint8,uint8);
Joystick_State getJoystickState(void);

#endif /* DDRVJOYSTICK_H_ */
