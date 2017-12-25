#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ABC.h"

void initPF(){
		/////////LED TEST////////////////
	SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
  GPIO_PORTF_DIR_R |= 0x0E;   // make PF1, 2 and 3 out
  GPIO_PORTF_AFSEL_R &= ~0x0E;// disable alt funct on PF1, 2 and 3
  GPIO_PORTF_DEN_R |= 0x0E;   // enable digital I/O on PF1,2 and 3
  GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF  
	//////////////////////////////////
}





void send(){
	float frequency;
	float Period;
	
	//PART_1
	//Get freq wanted from laptop
	
	frequency = 4;//test any frequency for now
	Period = 1/frequency;
	
	
	//PART_2 //Sending square wave
	while(1)
	{
	//toggle some port that's connected to the other tiva?
	//test led for now
	GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x0E; // toggle PF
	
	//Wait 1ms for a number of Period*1000 because 1s=1000ms
	SysTick_Wait_1ms(Period*1000);
	}
	
}

void receive(){
	
	//PART_3
	//Get PERIOD from some port that's connected to the other tiva?
	int period_time;
	period_time = Timer0A_periodCapture();
	
	while(1)
	{
	//PART_4
		//Send period time (or Freq) to laptop by UART
		//test with the LED for now
		GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R^0x0E; // toggle PF
    SysTick_Wait(period_time/2);
	}
	
}


int main(void){ 
	
		fpuInit();						//initalizes floating point
		SysTick_Init();				//initalizes systick
		initPF();      				//initalizes port F
		Timer0Capture_init(); //initalizes timer0
	
	send();
	//receive();

	return 0;
}



























