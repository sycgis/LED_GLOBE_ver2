#include "stm32f10x.h"
#include "lcd.h"
#include "math.h"
#include "freq.h"
#include "stdio.h"
#include "animation.h"
#include "APA102C.h"
#include "TextDisplay.h"
#include "USART.h"
#include "LaunchKeys.h"

#define DELAY_CONST 0.07058294738 // 10^6/(196774*SCREEN_WIDTH)

char freq_str[20];
uint16_t oldv,period,oldfrequency;
uint16_t freq;
uint16_t hall_test;
uint32_t sweep = 0xff000000;
unsigned int delay;
int     delay_offset;
uint8_t pressed,pressed2;
unsigned char  byte;




void KEY_CONFIG(void);
void setAllColor(uint8_t R, uint8_t G, uint8_t B, uint8_t Br);
void update(uint8_t forceUpdate);
void Delayus(int duration);
void TIM2_IRQHandler(void);
void Test(void);
void LCD_TEST();

void INITGPIO_IN();
void INITGPIO_IN2();
void INITGPIO_OUT();
int Check();
void ConvertToPitch(uint16_t button, uint16_t mode);
void __attribute__((weak)) osa_mdelay(unsigned int msec);
void __attribute__((weak)) delay_us(unsigned int usec);

int main(void)
{
	LCD_INIT();
	FREQ_INIT();
	KEY_CONFIG();
	APA102C_INIT();
	USART_INIT();
	
	INITGPIO_OUT();
	INITGPIO_IN();
	INITGPIO_IN2();
	
	setAllColorTest();
	delay =19;
	delay_offset = 0;
  while (1) 
	{
		
		//LED test
		//LED test start frame
		
		if(GPIOC->IDR & 0x2000)
			{
				// KEY 2 pressed 
				
				struct Param test = {0,0,0,0,0,255,110,199,32};
				test.x = 5;
				test.y = 14;
				test.width = 10;
				test.Red = 255;
				test.Blue = 110;
				test.Green = 199;
				test.Brightness = 32;
				test.func_num = 0;
				test.cmd = 10;
				test.cmd2 = 1;

				test.text = "H A R D E R";
				test.duration_fix = 100;
				test.duration= 100;
				addLayer(test);
				
				if(!pressed && delay_offset >0){
				delay_offset-= 1;
				pressed = 1;
				}
			}
			else{
				pressed = 0;
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
				test.Brightness = 32;
				test.func_num = 1;
				test.cmd = 10;
				test.cmd2 = 1;
				test.width = 5;
				test.text = "A";
				test.duration = 0;
				test.duration_fix = 100;
				addLayer(test);
				
			if(!pressed2){
			delay_offset += 10;
			pressed2 = 1;
			}
				
		}
		else{
			pressed2 = 0;
		}
		
		LCD_DrawString(0,0, "Delayt:                 ");
		sprintf(freq_str,"%d",delay_offset);
		LCD_DrawString(100,0, freq_str);		
		updateAnimation(4*period/1000);
		LCD_TEST();
		//displayNext();
		//delay_us(delay);		
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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//Measures the difference between to interrupts. Output's the frequency in hz
void TIM2_IRQHandler(void)
{
	uint16_t  newv;
  if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET) {
			TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
			
			current_col = 0;
			
      newv = TIM_GetCapture3(TIM2);
      if(GPIOA->IDR & GPIO_Pin_2) {
				
				LCD_DrawString(0,25, "Old value:                 ");
				sprintf(freq_str,"%d",oldv);
				LCD_DrawString(100,25, freq_str);
				LCD_DrawString(0,50, "New value:                 ");
				sprintf(freq_str,"%d",newv);
				LCD_DrawString(100,50, freq_str);
				
				period = (newv > oldv)? (newv - oldv) : (0xffff - oldv + newv);
				oldv = newv;
      }
			
			freq = 250000/period;
			
			LCD_DrawString(0,75, "Period:                 "); 
			sprintf(freq_str,"%d",period);
			LCD_DrawString(100,75, freq_str);	
			
			LCD_DrawString(0,100, "Frequency:                 "); 
			sprintf(freq_str,"%d",freq);
			LCD_DrawString(100,100, freq_str);	
			
		 delay = 4*period/SCREEN_WIDTH + delay_offset; // in us.
		 //updateAnimation(4*period/1000);
		 ConvertToPitch(Check(),1);
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

			LCD_DrawDot(30+i,70+j,color);
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
