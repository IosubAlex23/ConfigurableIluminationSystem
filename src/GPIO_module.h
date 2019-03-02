/*
 * GPIO_module.h
 *
 *  Created on: 24 apr. 2018
 *      Author: Alex
 */

#ifndef GPIO_MODULE_H_
#define GPIO_MODULE_H_

extern void GPIO_init(void);
extern void GPIO_set_GPIOA_pin_mode(uint8 pin, uint8 mode);

extern void GPIO_set_GPIOB_pin_mode(uint8 pin, uint8 mode);
extern void GPIO_set_portB_pin(uint8 pin,uint8 value);
extern void GPIO_set_portB_pinGroup(uint8 value, uint8 bit_lenght, uint8 bit_poz);


#endif /* GPIO_MODULE_H_ */
