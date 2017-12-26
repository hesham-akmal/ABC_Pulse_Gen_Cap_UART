#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "ABC.h"
#include "TExaS.h"

void EnableInterrupts(void);  // Enable interrupts

void generate(){
	volatile float frequency; // should probably stick to int
	volatile float Period;
	
	//PART_1
	//Get freq wanted from laptop
	USB_UART_OutString("Please enter frequency in MHz: ");
	
	//frequency = USB_UART_InUDec();
	frequency = 2;
	Period = 1/frequency;
	
	//Print Period test/////////////////////////////////////////////
	USB_UART_OutString("P = ");
	USB_UART_OutFloat(Period);
	////////////////////////////////////////////////////////////////
	
	//PART_2
	//Send square wave
	
	/************///PWM implementation
	// counts = ( sys_T * uart freq ) - 1 ??
	//PWM_setCountAndStart( (1/80000000) * frequency );
	PWM_setCountAndStart(1000); //////////////////////////////////////////CHANGE THIS
	
	//TEST PRINT COUNTS
	//USB_UART_OutInt( (1/80000000) * frequency );
	/////////////////////////////////
}
 
void receive(){
	//PART_3
	//recieve square wave
	int period_time;
	period_time = Timer0A_periodCapture();
	
	//PART_4
	//send freq number to laptop
	USB_UART_OutString("Time difference = ");
	USB_UART_OutInt(period_time);
	USB_UART_OutString("\n");
}
		
int main(void){ 
	
	TExaS_Init();             // initialize grader, set system clock to 80 MHz
  USB_UART_Init();          // initialize USB UART
  EnableInterrupts();       // needed for TExaS
	
	fpuInit();						//initalizes floating point
	SysTick_Init();				//initalizes systick
	
	PWM_init();						//initalizes timer1 as PWM
	Timer0Capture_init(); //initalizes timer0 as edge-time capture mode
	
	//generate();
	
	while(1)
	{
	receive(); 
	SysTick_Wait_1ms(1000);
	}
}



























