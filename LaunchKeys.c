#include "LaunchKeys.h"
#include "stm32f10x_gpio.h"
	//https://www.youtube.com/watch?v=RGkIHFQf8-w
	//https://www.embeddedrelated.com/showarticle/519.php
	/*
	KEYS USED: A0, A2, A5, A7, C13
	main.c
	A0: Key1	input
	C13: Key 2 input
	freq.c
	A2: Hall Effect Sensor input
	A0: Key 1 input (test)
	APA102C.c
	A5: CLOCK
	A7:	DATA	
	*/
	
	/*
#define COLUMN1 = GPIO_Pin_2;
#define COLUMN2 = GPIO_Pin_3;
#define COLUMN3 = GPIO_Pin_4;
#define COLUMN4 = GPIO_Pin_5;
#define ROW1 = GPIO_Pin_6;
#define ROW2 = GPIO_Pin_7;
#define ROW3 = GPIO_Pin_8;
#define ROW4 = GPIO_Pin_9;
*/


#define COLUMN1		              ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define COLUMN2                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define COLUMN3                 ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define COLUMN4                 ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define ROW1                    ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define ROW2    	              ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define ROW3  	                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define ROW4	                  ((uint16_t)0x0010)  /*!< Pin 4 selected */

struct Param null;
struct Param animation_list[BUTTON_NUM][EFFECT_NUM];
_Bool ButtonOn[17];

	//Assuming 4x4 Launch Keys + 4 Modes	
void INITGPIO_OUT()
{
	//4 OUTPUT pins: G2, G3, G4, G5
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void INITGPIO_IN()
{
	//4 INPUT pins: G2, G3, G4, G5
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_12 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*
void INITGPIO_IN2()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
*/

int Check()
{
	uint16_t result = 0;
	//Init all pins to LOW
	GPIOC->BRR = COLUMN1;
	GPIOC->BRR = COLUMN2;
	GPIOC->BRR = COLUMN3;
	GPIOC->BRR = COLUMN4;
	
	//set Pin2(Column 1) to high
	//Check if any of Pin 6/7/8/9(Rows 1,2,3,4) inputs are high
	//if none of the inputs high, Set Pin2 to low
	//Set Pin3(Column 2) to high
	//Check if any of Pin 6/7/8/9 inputs are high
	GPIOC->BSRR = COLUMN1;
	if(GPIO_ReadInputDataBit(GPIOC, ROW1)){
		//Button A Pressed
		result = result + 1;
	}
	else if(GPIO_ReadInputDataBit(GPIOC, ROW2)){
		//Button B Pressed
		result = result + 2;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW3)){
		//Button C Pressed
		result = result + 4;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW4)){
		//Button D Pressed
		result = result + 8;
	}
	GPIOC->BRR = COLUMN1;
	
	GPIOC->BSRR = COLUMN2;
	if(GPIO_ReadInputDataBit(GPIOC, ROW1)){
		//Button E Pressed
		result = result + 16;
	}
	else if(GPIO_ReadInputDataBit(GPIOC, ROW2)){
		//Button F Pressed
		result = result + 32;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW3)){
		//Button G Pressed
		result = result + 64;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW4)){
		//Button H Pressed
		result = result + 128;
	}
	GPIOC->BRR = COLUMN2;
	
	GPIOC->BSRR = COLUMN3;
	if(GPIO_ReadInputDataBit(GPIOC, ROW1)){
		//Button I Pressed
		result = result + 256;
	}
	else if(GPIO_ReadInputDataBit(GPIOC, ROW2)){
		//Button J Pressed
		result = result + 512;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW3)){
		//Button K Pressed
		result = result + 1024;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW4)){
		//Button L Pressed
		result = result + 2048;
	}
	GPIOC->BRR = COLUMN3;
	
	GPIOC->BSRR = COLUMN4;
	if(GPIO_ReadInputDataBit(GPIOC, ROW1)){
		//Button M Pressed
		result = result + 4096;
	}
	else if(GPIO_ReadInputDataBit(GPIOC, ROW2)){
		//Button N Pressed
		result = result + 8192;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW3)){
		//Button O Pressed
		result = result + 16384;
	}
	else if (GPIO_ReadInputDataBit(GPIOC, ROW4)){
		//Button P Pressed
		result = result + 32768;
	}
	GPIOC->BRR = COLUMN4;
	return result;
}
void process_animation(int n){
	int i;
	
	for(i = 0; i < EFFECT_NUM; i++){
		if(animation_list[n][i].duration != -1){
			addLayer(animation_list[n][i]);
		}
	}
}
void ConvertToPitch(uint16_t button, uint16_t mode)
{
	int i;
	for(i=0; i<17; ++i){
		if ((button>>i & 0x1)){
			if(!ButtonOn[i]){
				process_animation(i);
				ButtonOn[i] = 1;
				noteOn(1, i+12, 127);
			}	
		}
		else{
			if(ButtonOn[i]){
				ButtonOn[i] = 0;
				noteOff(1,i+12,127);
			}
		}
	}
}
void ANIMATION_INIT(void){
	int i,j;
	null.duration = -1;
	for(i = 0; i < BUTTON_NUM; i++){
		for(j = 0; j < EFFECT_NUM; j++){
				animation_list[i][j] = null;
			}
		}
	animation_list[0][0] = bgColor(0,0,0);
	animation_list[0][1] = textCenter("W O R K  I T", 255,0,146);
		
	animation_list[1][0] = bgColor(0,0,0);
	animation_list[1][1] = textCenter("M A K E  I T", 34,141,255);
		
	animation_list[2][0] = bgColor(0,0,0);
	animation_list[2][1] = textCenter("     D O  I T", 255,0,146);
		
	animation_list[3][0] = bgColor(0,0,0);
	animation_list[3][1] = textCenter("M A K E S  U S", 34,141,255);
	
	animation_list[4][0] = bgColor(255,0,146);
	animation_list[4][1] = textCenter("H A R D E R", 0,0,0);
		
	animation_list[5][0] = bgColor(34,141,255);
	animation_list[5][1] = textCenter("B E T T E R", 0,0,0);
		
	animation_list[6][0] = bgColor(255,0,146);
	animation_list[6][1] = textCenter("F A S T E R", 0,0,0);
		
	animation_list[7][0] = bgColor(34,141,255);
	animation_list[7][1] = textCenter("S T R O N G E R", 0,0,0);
	
	animation_list[8][0] = swipeColor(255,0,146,1,1,300);
	
	animation_list[9][0] = swipeColor(255,202,27,1,0,300);
	
	animation_list[10][0] = swipeColor(34,141,255,0,1,300);
	
	animation_list[11][0] = swipeColor(186,1,255,0,0,300);
}