/*
 * pwm.h
 *
 *  Created on: Mar 30, 2018
 *      Author: csenger
 */

#ifndef PWM_H_
#define PWM_H_
#include "derivative.h"
#include "types.h"

extern void Pwm_vFTM2Init(void);
extern void Pwm_u16SetChannelDutyCycle(uint32* channel,uint16_t u16Duty);

#endif /* PWM_H_ */
