#include "stm32f10x.h"
#include "stm32f10x_tim.h"
/**
*    Pulse signal frequency detection by using internal interrupt. 
*    Based on tutorial: http://blog.naver.com/PostView.nhn?blogId=gauya&logNo=220241073406
*    
*    Hall effect sensor at PA2
**/

#define SYSTEM_CLK 72000000

void FREQ_INIT(void);

//void TIM2_IRQHandler(void);
