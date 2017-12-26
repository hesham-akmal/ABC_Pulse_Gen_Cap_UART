#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "ABC.h"
#include "TExaS.h"

void EnableInterrupts(void);  // Enable interrupts

void float_toCharArr(float f, unsigned char * charArr){
	int intValue;
	float diffValue;
	int anotherIntValue;
	intValue = (int)f;
	diffValue = f - (float)intValue;
	anotherIntValue = (int)(diffValue * 1000.0);
	sprintf(charArr, "\nP= %d.%d\n", intValue, anotherIntValue); //ignore warning
}

void generate(){
	volatile float frequency; // should probably stick to int
	volatile float Period;
	unsigned char PeriodString[100] ;
	
	volatile float testF;
	unsigned char testC[100] ;
	
	//PART_1
	//Get freq wanted from laptop
	USB_UART_OutString("Please enter frequency in MHz: ");
	
	frequency = USB_UART_InUDec();
	Period = 1/frequency;
	
	//Print Period test/////////////////////////////////////////////
	float_toCharArr(Period , PeriodString);
	USB_UART_OutString(PeriodString);
	////////////////////////////////////////////////////////////////
	
	//PART_2
	//Send square wave
	
	/************///PWM implementation
	// counts = ( sys_T * uart freq ) - 1 ??
	//PWM_setCountAndStart( (1/80000000) * frequency );
	PWM_setCountAndStart(0xffff); //////////////////////////////////////////CHANGE THIS
	
	//TEST PRINT COUNTS
	//testF = (1/80000000) * frequency;
	//float_toCharArr(testF, testC);
	//USB_UART_OutString(testC);
	/////////////////////////////////
}
 
void receive(){
	//PART_3
	//recieve square wave
	int period_time;
	unsigned char period_time_charArr[100];
	period_time = Timer0A_periodCapture();
	
	//convert int to string
	sprintf( period_time_charArr , "%d", period_time); //ignore warning
	
	//PART_4
	//send freq number to laptop
	USB_UART_OutString("Time difference = ");
	USB_UART_OutString(period_time_charArr);
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
	
	generate();
	
	while(1)
	{
	receive(); 
	SysTick_Wait_1ms(1000);
	}
}



























