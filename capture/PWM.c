#include "tm4c123gh6pm.h"
#include "ABC.h"
#include "UART.h"

void PWM_init(void)
{
    SYSCTL_RCGCTIMER_R |= 0x02;     // Enable clock to Timer 1

		TIMER1_CTL_R &= ~1;
		TIMER1_CFG_R = 0x00000004;
		
    TIMER1_TAMR_R |= 0xB;
		TIMER1_TAMR_R |= 0x3B9ACA00;
		
		TIMER1_TAILR_R = 0x4C4B400; //0x4C4B400 = 80 000 000
		
		TIMER1_TAMATCHR_R = 0x0;
		
		//TIMER1_TAILR_R = 0xffffffff; //largest num of counts, still too fast
		//test();
}

void PWM_start(void){
 TIMER1_CTL_R |= 1;
}

void PWM_setCount(uint16_t counts){
 TIMER1_TAILR_R = counts;
}

void test(void){

		PWM_start();
		while(1)
		{
			if( TIMER1_RIS_R & 0x04 )
			{
			 TIMER1_ICR_R = 0x04; 	//NOT WORKING, RIS IS NOT CLEARED!!! WHY?
			 USB_UART_OutChar('x');
			}
		}
}

