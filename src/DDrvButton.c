/*
 * DDrvButton.c
 *
 *  Created on: 19 mai 2018
 *      Author: Alex
 */

#include "DDrvButton.h"


void ButtonInit(uint8 btnPin){
	//GPIOA_PDDR &= ~(1 << btnPin);   	// Input port for pin rxPin
	//GPIOA_PIDR &= ~(1 << btnPin);   	// Enable inputs
	GPIO_set_GPIOA_pin_mode(btnPin, PIN_MODE_IN);
	PORT_PUE0 |= 1 << btnPin;	// pullup resistor on PORTA1
}

Button_State isGPIOA_ButtonPressed(uint8 btnPin){
	uint8 i, samples = 0;
	Button_State btn_State = Button_NotPressed;

	for (i = 0; i < 10; i++) {
		if (GPIOA_PDIR & (1 << btnPin)) {
			samples = 0;
		} else {
			samples++;
		}
		delay_ms(5);
	}

	if (samples >= 5) {
		delay_ms(50);
		while (!(GPIOA_PDIR & (1 << btnPin)))
			;	// {
		btn_State = Button_Pressed;
	}
	return btn_State;
}
