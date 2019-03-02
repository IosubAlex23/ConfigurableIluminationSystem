/*
 * Application.h
 *
 *  Created on: 27 mai 2018
 *      Author: Alex
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "types.h"
#include "LCD_Driver.h"
#include "DDrvJoystick.h"
#include "DDrvLeds.h"
#include "DDrvButton.h"

typedef enum{
	MenuLocation_MainMenu=0u,
	MenuLocation_LedMenu=1u,
	MenuLocation_LevelMenu=2u,
} MenuLocation;

void App_vInit(void);
void App_vRefreshDisplay(void);
void App_vCheckUserInput(void);
void App_vSetSelector(uint8 location);

#endif /* APPLICATION_H_ */
