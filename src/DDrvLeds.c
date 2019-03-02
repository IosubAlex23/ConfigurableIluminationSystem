/*
 * DDrvLeds.c
 *
 *  Created on: 26 mai 2018
 *      Author: Alex
 */

#include "DDrvLeds.h"

#define NumberOfLeds 4

uint32 LEDs_level = LED_Level5;

void LED_vInit(void) {
	SIM_PINSEL1 |= 0x5a; /* Selects the PINS for FTM2; PTF0, PTF1, PTD0, PTD1 */
	//FTM2_C0SC = 0x00000038; /* Edge-Aligned PWM High-true pulses (clear Output on match) */
	uint8 i;
	uint32 * module_SC;
	for (i = 0; i < NumberOfLeds; i++) {
		module_SC = &FTM2_C0SC + (2 * i);
		*module_SC = 0x00000038;
	}
}
/*void LED_vTurnOFF(uint32 * led){
 *led =0;
 }*/

void LED_vTurnOFF(struct Led * led) {
	//*led->channel = 0;
	Pwm_u16SetChannelDutyCycle(led->channel,0);
}

/*void LED_vTurnON(struct Led * led) {
 *led->channel = led->led_level;
 }*/
void LED_vTurnON(struct Led * led) {
	if (led->led_status == LED_ON)
		//*led->channel = LEDs_level;
		Pwm_u16SetChannelDutyCycle(led->channel,LEDs_level);
}

void LED_vSetLevel(LED_Level level) {
	LEDs_level = level;
}

LED_Level LED_ui32getLevel() {
	return LEDs_level;
}

void LED_vUpdateLEDS(struct Led* leds, uint8 ledsNumber) {
	uint8 i;
	for (i = 0; i < ledsNumber; i++) {
		LED_vTurnON(&leds[i]);
	}
}
