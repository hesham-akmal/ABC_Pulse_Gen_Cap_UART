#include "tm4c123gh6pm.h"
#include "ABC.h"
#include "UART.h"

void PWM_setCountAndStart(uint16_t counts)
{
 TIMER1_TAILR_R = counts;
 TIMER1_CTL_R |= 1;
}

void PWM_init(void)
{
    SYSCTL_RCGCTIMER_R |= 0x02;     // Enable clock to Timer 1
		TIMER1_CTL_R &= ~1;
		TIMER1_CFG_R = 0x00000004;
    TIMER1_TAMR_R |= 0xA;
		
	//TIMER1_TAILR_R = 0x4C4B400; //0x4C4B400 = 80 000 000
	//	TIMER1_TAMR_R |= 0x200;
	//	TIMER1_TAMATCHR_R = 0x0;
	//	TIMER1_CTL_R |= 0xC;
		
		//PWM_setCountAndStart(9999); //largest num of counts, still too fast
		//test();
}

/*void test(void)
{
		while(1)
		{
			if( TIMER1_RIS_R & 0x04 )
			{
			 TIMER1_ICR_R |= 0x04;
			 USB_UART_OutChar('X');
			}
			 else
				USB_UART_OutChar('0');
		}
}*/

