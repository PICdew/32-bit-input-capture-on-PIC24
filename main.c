#include "config.h"					//configuration words - for C30. Use config.h for XC16
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "tmr23.h"						//we use 32-bit tmr23
#include "ic1.h"						//we use input capture
#include "ic2.h"						//we use input capture
#include "ic3.h"						//we use input capture
#include "ic4.h"						//we use input capture
#include "ic5.h"						//we use input capture

//hardware configuration
#define LED_PORT			LATB
#define LED_DDR				TRISB
#define LED					(1<<0)
//end hardware configuration

//global defines

//global variables
volatile uint32_t tick, tick0, tick1;
uint16_t tick_lsw, tick_msw;


//obtain the captured value and calculate the duration
void tick_get(void) {
	//has to clear MSW/IC4's flags or input capture wouldn't happen
	tick1=IC4BUF; IFS2bits.IC4IF = 0;	//has to do so as IC4's interrupt is disabled
	tick1=(tick1 << 16) | ic5_get();	//form the 32-bit capture value
	tick = tick1 - tick0;				//calculate the 32-bit duration
	tick0 = tick1;						//update tick0
	IO_FLP(LED_PORT, LED);
}

int main(void) {
	
	mcu_init();							//reset the mcu
	IO_OUT(LED_DDR, LED);				//led as output
	
	//join TIM2/3 to form a 32-bit timer
	tmr23_init(TMR_PS_1x);				//initialize tmr23 as 32-bit free running time base for IC4/5
	
	//initialize ic4/5
	//ic5 on tmr2/LSW, ic4 on tmr3/MSW. 
	//***important***: both modules use the same pin (RP6) as input capture pin
	ic5_init(); ic4_init();				
	ic5_act(tick_get);					//install user handler
	ei();
	while (1) {
		//simulator not showing 32-bit values correctly
		//so we decompose it to two 16-bit values
		//tick = (tick_msw<<16) | tick_lsw
		//convert tick value to string
		tick_msw = tick >> 16;			//=4
		tick_lsw = tick;				//=6784
		//4*65536 + 6784 = 400000 ticks, as expected
		//we are measuring a 10hz pulse on a PIC24 with 8Mhz Fosc
		//100ms @ 4Mhz Fcy = 400000 ticks
	}
}
