#include "freq.h"
#include "lcd.h"
/**
*    Pulse signal frequency detection by using internal interrupt. 
*    Based on tutorial: http://blog.naver.com/PostView.nhn?blogId=gauya&logNo=220241073406
*    
*    Hall effect sensor at PA2
**/

void NVIC_INIT(void)
{
	//Nested Vector Interrupt Control Initialize
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void GPIO_INIT(void)
{
	//Hall effect sensor at PA2
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void GPIO_INITK1(void)
{
	//For K1 button
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ICTIM_INIT(void)
{
	//Input Capture Timer Init
	TIM_ICInitTypeDef  TIM_ICInitStructure; // Declare Variable
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; // Timer 2 channel 3
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // Rising Edge

  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;// 0x0 ~ 0xf
  TIM_ICInit(TIM2, &TIM_ICInitStructure); // Initialize Timer2
	TIM_ITConfig(TIM2,TIM_IT_CC3, ENABLE); // CC - Capture Compare, CCER - Capture Compare Enable Register
}
void TIM3_CONFIG (void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	// 1MHz
	TIM_TimeBaseStructure.TIM_Period = 287; // 72*4 1 tick is 250000Hz 
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// 50%
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 10; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM3,ENABLE);
}
void TIMBASE_INIT(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
  TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);	
	TIM_TimeBaseStructure.TIM_Period       = 0xffff; // (72000000Hz / 4 / 128) = 140625 Hz = 7us, 
	//count up to 65535
  TIM_TimeBaseStructure.TIM_Prescaler     = 0; //Increment clock every 128th tick
  TIM_TimeBaseStructure.TIM_ClockDivision    = 0; //Divide clock by 4
  TIM_TimeBaseStructure.TIM_CounterMode     = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_PrescalerConfig(TIM2, 0, TIM_PSCReloadMode_Immediate); 
	
	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);
	TIM_SelectInputTrigger(TIM2, TIM_TS_ITR2);
	
	TIM_Cmd(TIM2, ENABLE);
}

void OCTIM_INIT(void)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
}

void FREQ_INIT(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable Real Time Clock Control APB on Timer 2
	NVIC_INIT(); // Interrupt Vector for Frequency Measurement
	GPIO_INIT(); // Hall Effect Sensor at PA2
	//GPIO_INITK1(); //For K1 button test
	ICTIM_INIT(); // Input Capture Timer for Frequency Measurement time difference
	TIM3_CONFIG();
	TIMBASE_INIT(); // Setup Timer Timebase : Timer 2
	OCTIM_INIT(); // Output Compare Timer Init	
}
