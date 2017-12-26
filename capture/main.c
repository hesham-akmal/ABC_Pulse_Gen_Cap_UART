#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "ABC.h"
#include "TExaS.h"

void EnableInterrupts(void);  // Enable interrupts

void initPF(){
	/////////FOR LED TEST////////////////
	SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
  GPIO_PORTF_DIR_R |= 0x0E;   // make PF1, 2 and 3 out
  GPIO_PORTF_AFSEL_R &= ~0x0E;// disable alt funct on PF1, 2 and 3
  GPIO_PORTF_DEN_R |= 0x0E;   // enable digital I/O on PF1,2 and 3
  GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF  
	//////////////////////////////////
}


void float_toCharArr(float f, unsigned char * charArr){
	int intValue;
	float diffValue;
	int anotherIntValue;
	intValue = (int)f;
	diffValue = f - (float)intValue;
	anotherIntValue = (int)(diffValue * 1000.0);
	sprintf(charArr, "\nP= %d.%d\n", intValue, anotherIntValue); //ignore warning
}



void send(){
	volatile float frequency; // should probably stick to int
	volatile float Period;
	unsigned char PeriodString[100] ;
	
	
	//PART_1
	//Get freq wanted from laptop
	frequency = USB_UART_InUDec();
	//frequency = 2;//test
	Period = 1/frequency;
	
	//Print Period test/////////////////////////////////////////////
	float_toCharArr(Period , PeriodString);
	USB_UART_OutString(PeriodString);
	////////////////////////////////////////////////////////////////
	
	//PART_2 //Send square wave via TRANSMITTER_UART
	
	/************///PWM implementation
	// counts = ( sys_T * uart freq ) - 1
	/*PWM_setCount( (1/80000000) * frequency ); 
	while(1)
	{
	//PWM_waitTillFlag();
	//TIVA_UART_OutChar(1);
	}*/
	
	
	/************///Systick implementation
	while(1)
	{
	//test led for now
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x0E; // toggle PF
	//Wait 1ms for a number of Period*1000 as 1s=1000ms
	SysTick_Wait_1ms(Period*1000);
	}
}
 
void receive(){
	
	//PART_3
	//recieve square wave from RECEIVER_UART
	
	//This part needs work
	int period_time;
	unsigned char period_time_charArr[100];
	period_time = Timer0A_periodCapture();
	
	//convert int to string
	sprintf( period_time_charArr , "%d", period_time); //ignore warning
	
	//PART_4
	//send freq number to laptop
	USB_UART_OutString(period_time_charArr);
	
}
		
int main(void){ 
	
	Timer0Capture_init(); //initalizes timer0 as edge-time capture mode
	
	TExaS_Init();             // initialize grader, set system clock to 80 MHz
  USB_UART_Init();              // initialize USB UART
	TIVA_UART_Init();              // initialize TIVA UART
  EnableInterrupts();       // needed for TExaS (very important)
	
	fpuInit();						//initalizes floating point
	SysTick_Init();				//initalizes systick
	initPF();      				//initalizes port F for LED testing
	PWM_init();						//initalizes timer1 as PWM  
	
	//send();
	receive(); 

	return 0;
}



























