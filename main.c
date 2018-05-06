#include "main.h"

int main(void)
{
	NVIC_Configuration();
	
	LCD_INIT();
	FREQ_INIT();
	KEY_CONFIG();
	APA102C_INIT();
	
	USART_INIT();
	Status = SD_Init();
	
	//SD uses C 8 9 10 11 12 and D 0 1 2 3
	
	INITGPIO_OUT();
	INITGPIO_IN();
	//INITGPIO_IN2();
	INITGPIO_MODE();
	ANIMATION_INIT();
	

	//SD_MultiBlockTest();
	//sd_test();
	//setAllColorTest();
	delay =1258;
	delay_offset = 0;
	//image(putImage(1,58));
  while (1) 
	{
		
		//LED test
		//LED test start frame
		
		if(GPIOC->IDR & 0x2000)
			{
				// KEY 2 pressed 
				
				struct Param test;
				
				test.x = 0;
				test.y = 14;
				test.Red = 0;
				test.Blue = 0;
				test.Green = 255;
				test.Brightness = 1;
				test.func_num = 0;

				test.text = "H A R D E R";
				test.duration= 10000;
				test.duration_fix = 100000;
				getData(test);
				
				
			}
		
		if(GPIOA->IDR & 0x0001)
		{
			//KEY 1 Pressed
				struct Param test = {0,0,0,0,0,255,110,199,32};
				test.x = 0;
				test.y = 0;
				test.Red = 57;
				test.Blue = 20;
				test.Green = 255;
				test.Brightness = 31;
				test.Red2 = 255;
				test.Blue2 = 0;
				test.Green2 = 0;
				test.Brightness2 = 31;
				test.func_num = 4;
				test.cmd = 10;
				test.cmd2 = 0;
				test.width = 5;
				test.text = "A";
				test.duration = 1000;
				test.duration_fix = 100;
				setAllColor(test);
				
		}
		if(HIT){
		//current_col = 0;
		 freq = 250000/period;
		 delay= 4*period/SCREEN_WIDTH + delay_offset; // in us.
		 if(prev_delay > 1000) delay = prev_delay;
		 updateAnimation(4*period/1000);
		 //LCD_TEST();
		 modeCheck();
		 ConvertToPitch(Check());
		 HIT = 0;
			
		}
		delay_us(delay);
		//modeCheck();
		//ConvertToPitch(Check());
		LCD_DrawString(0,100,"CHECK:                           " );
		sprintf(freq_str,"%d",Check());
		LCD_DrawString(100,100, freq_str);	
		//updateAnimation(4*31250/1000);
		//LCD_TEST();
		// ConvertToPitch(Check(), 1);
		//updateFrame();
		displayNext();
		
  }
}


void KEY_CONFIG (void)
{		
	/* Task 2: Configure K1 and K2 as input */
	//KEY 1
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //Will this Work??
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//KEY 2
	//GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/*
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	*/
}

//Measures the difference between to interrupts. Output's the frequency in hz
void TIM2_IRQHandler(void)
{
	
	uint16_t  newv;
  if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET) {
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
      newv = TIM_GetCapture3(TIM2);
		
      if(GPIOA->IDR & GPIO_Pin_2) {
				
				period = (newv > oldv)? (newv - oldv) : (0xffff - oldv + newv);
				oldv = newv;
				current_col = 0;
				HIT= 1;
      }
  }
	
}
void sd_test(void){
	int i,j,k;
	k = 54;
		for (j = LED_LEN -1 ; j >= 0; j--)
	{
		for(i = 0; i < 58; i++)
		{
			if(k + 3<58*36*3){
			master_channel[i][j][CH_RED] = Buffer_MultiBlock_Rx[k+2];
			USARTsendByte(USART1, Buffer_MultiBlock_Rx[k]);
			master_channel[i][j][CH_GREEN] = Buffer_MultiBlock_Rx[k+1];
			USARTsendByte(USART1, Buffer_MultiBlock_Rx[k+1]);
			master_channel[i][j][CH_BLUE]= Buffer_MultiBlock_Rx[k];
			USARTsendByte(USART1, Buffer_MultiBlock_Rx[k+2]);
			k+=3;
			if(i == 57) k +=2;
			}
			}
		}
	
}
/*
*	displays the projection on the lcd screen
*/
void LCD_TEST(void){
	int i,j;
	uint8_t  R,G,B;
	uint16_t color;
	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		for(j = 0; j < LED_LEN; j++)
		{
			R = master_channel[i][j][CH_RED];
			G = master_channel[i][j][CH_GREEN];
			B = master_channel[i][j][CH_BLUE];
			
			color = (R & 0xf8) << 8 | (G & 0xfC) << 5| B >>3;

			LCD_DrawDot(5+i,70+j,color);
			}
		}
	}

void Delayus(int duration)
{
		while(duration--) 
		{
			int i=0x02;				
			while(i--)
			__asm("nop");
		}
}

void __attribute__((weak)) osa_mdelay(unsigned int msec)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)msec*(HSE_VALUE/1000);
	SysTick->VAL =0x00;		// clear Count flag
	SysTick->CTRL=0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));	// wait Count flag set
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}

void __attribute__((weak)) delay_us(unsigned int usec)
{
	uint32_t temp;
	SysTick->LOAD=(uint32_t)usec*(HSE_VALUE/1000000);
	SysTick->VAL =0x00;		// clear Count flag
	SysTick->CTRL=0x01;
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));	// wait Count flag set
	SysTick->CTRL=0x00;
	SysTick->VAL =0X00;
}
