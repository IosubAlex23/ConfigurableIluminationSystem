/*
 * GPIO_module.c
 *
 *  Created on: 24 apr. 2018
 *      Author: Alex
 */
#include "types.h"
#include "GPIO_module.h"
#include "derivative.h"

void GPIO_init(void){

}

void GPIO_set_GPIOB_pin_mode(uint8 pin, uint8 mode){
/*	if(pin > 7)
		return;*/
	if(mode == PIN_MODE_IN){
		GPIOB_PDDR &= ~(1 << pin);
		GPIOB_PIDR &= ~(1 << pin);
	}
	else{
		GPIOB_PDDR |= 1 << pin;
		GPIOB_PIDR |= 1 << pin;
	}
}

void GPIO_set_GPIOA_pin_mode(uint8 pin, uint8 mode){
/*	if(pin > 7)
		return;*/
	if(mode == PIN_MODE_IN){
		GPIOA_PDDR &= ~(1 << pin);
		GPIOA_PIDR &= ~(1 << pin);
	}
	else{
		GPIOA_PDDR |= 1 << pin;
		GPIOA_PIDR |= 1 << pin;
	}
}

void GPIO_set_portB_pin(uint8 pin, uint8 value){
	if(pin > 7)
			return;
	if(value == 0){
		GPIOB_PCOR = 1 << (pin+8);
	}
	else
		GPIOB_PSOR = 1 << (pin+8);
}


extern void GPIO_set_portB_pinGroup(uint8 value, uint8 bit_lenght, uint8 bit_poz){
	volatile uint32 tempReg;
	uint32 mask = 0;
	uint32 i;

	tempReg = GPIOA_PDOR;
	for(i=0; i<bit_lenght; i++)
		mask |= (1u<<i);
	mask = (mask << (bit_poz + 8));
	tempReg &= ~mask;
	tempReg |= (value << (bit_poz+8));
	GPIOA_PDOR = tempReg;
}























