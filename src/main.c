/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations SSKEAZ128M4 */
#include "clocks.h"
#include "UART.h"
#include "DDrvJoystick.h"
#include "DDrvButton.h"
#include "LCD_Driver.h"
#include "delay.h"
#include "pwm.h"
#include "DDrvLeds.h"
#include "Application.h"

int main(void) {
	init_clks_FEE_40MHz(); /* KEA128 clks FEE, 8MHz xtal: core 40 MHz, bus 20MHz */
	init_IRQs();
	init_delay();
	LCD_Init(); /* Initialization of LCD*/
	init_UART(); /* Initialize UART2 9600 baud, 1 stop, no parity no IRQ */
	Pwm_vFTM2Init();
	JoyStick_Init(12, 13); /* PTF4-5 */
	ButtonInit(0); /* GPIOA pin 0 */
	LED_vInit();
	App_vInit();
	while(1){
		App_vCheckUserInput();
		send_char('n');
	}
	return 0;
}
