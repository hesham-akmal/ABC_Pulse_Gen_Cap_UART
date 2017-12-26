#include <stdint.h>
#include "tm4c123gh6pm.h"
void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void SysTick_Wait_1ms(uint32_t delay);

void Timer0Capture_init(void);
int Timer0A_periodCapture(void);

void fpuInit(void);

void PWM_init(void);
void PWM_enable(void);
void PWM_setSeconds(uint16_t secs);
void test(void);
void PWM_setCount(uint16_t counts);

