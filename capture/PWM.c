#include "tm4c123gh6pm.h"
#include "ABC.h"
#include "UART.h"

void PWM_setCountAndStart(uint16_t counts)
{
 TIMER1_TAILR_R = counts;
 TIMER1_CTL_R |= 1;
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

void test2(void)
{
		PWM_setCountAndStart(0xffff);
		while(1)
				USB_UART_OutInt(	GPIO_PORTB_DATA_R & 0x10 );	
				
				
				/*if( TIMER1_TAR_R == 0 )
					{
		USB_UART_OutString(" _ ");
		USB_UART_OutInt(TIMER1_TAR_R);
					}*/
}

void PWM_init(void)
{
    SYSCTL_RCGCTIMER_R |= 0x02;      // Enable clock to Timer 1
		
		SYSCTL_RCGCGPIO_R |= 0x02;       // enable clock to PORTB
    GPIO_PORTB_DIR_R |= 0x10;        //make PB4 an output pin 
    GPIO_PORTB_DEN_R |= 0x10;        // make PB4 as digital pin 
    GPIO_PORTB_AFSEL_R |= 0x10;      // use PB4 alternate function
    GPIO_PORTB_PCTL_R &= ~0x000F0000;// configure PB4 for T1CCP0 
    GPIO_PORTB_PCTL_R |=  0x00070000;
		
		TIMER1_CTL_R &= ~1;
		TIMER1_CFG_R = 0x00000004;
    TIMER1_TAMR_R |= 0xA;
		TIMER1_TAMATCHR_R = 0x0;
		
		/*SYSCTL_RCGCGPIO_R |= 0x20;     			// enable clock to PORTF
    GPIO_PORTF_DIR_R |= 0x04;        		//make PF2 an output pin 
    GPIO_PORTF_DEN_R |= 0x04;        		// make PF2 as digital pin 
    GPIO_PORTF_AFSEL_R |= 0x04;     		// use PF2 alternate function
    GPIO_PORTF_PCTL_R &= ~0x00000F00; 	// configure PF2 for T1CCP0 
    GPIO_PORTF_PCTL_R |=  0x00000700;
		*/ 
		
		 TIMER1_TAMR_R |= 0x200; //enable intrupt
		// TIMER1_TAILR_R = 0x4C4B400; //0x4C4B400 = 80 000 000
		//TIMER1_CTL_R |= 0x04;
		//PWM_setCountAndStart(9999); //largest num of counts, still too fast
		test2();
}


