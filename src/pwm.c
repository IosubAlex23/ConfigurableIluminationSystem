#include "pwm.h"
extern void Pwm_vFTM2Init(void) {
	SIM_SCGC |= SIM_SCGC_FTM2_MASK; /* Sys Clk Gate Ctrl: enable bus clock to FTM2 */

	FTM2_SC = 0x00000001; // prescaler = 2
	FTM2_MOD = 50000; // 200 Hz
	FTM2_SC |= FTM_SC_CLKS(1); //BUS CLOCK
	// prescaler 2; FTM1_MOD = 50000;	
}

extern void Pwm_u16SetChannelDutyCycle(uint32* channel,uint16_t u16Duty) {
	// channel is CnV
	*channel = u16Duty;
}
