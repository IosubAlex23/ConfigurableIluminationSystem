/*
 * DDrvLeds.h
 *
 *  Created on: 26 mai 2018
 *      Author: Alex
 */

#ifndef DDRVLEDS_H_
#define DDRVLEDS_H_

#include "types.h"
#include "derivative.h"
#include "pwm.h"

typedef enum{
	LED_OFF=0u,
	LED_ON=1u,
} LED_Status;

typedef enum{
	LED_Level1=10000u,
	LED_Level2=20000u,
	LED_Level3=30000u,
	LED_Level4=40000u,
	LED_Level5=50000u,
} LED_Level;

struct Led{
	LED_Status led_status;
	LED_Level led_level;
	uint32 * channel;
};

void LED_vInit(void);
void LED_vTurnOFF(struct Led * led);
void LED_vTurnON(struct Led * led);
void LED_vSetLevel(LED_Level level);
void LED_vUpdateLEDS(struct Led* leds, uint8 ledsNumber);
LED_Level LED_ui32getLevel();


#endif /* DDRVLEDS_H_ */
