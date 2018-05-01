#include "APA102C.h"
#include "stm32f10x.h"
#include "stm32f10x_spi.h"

/*
*	APA102C library, based on github project : https://github.com/pe1mew/APA102-on-STM32
*														 reference for SPI: http://shinble.blogspot.hk/2015/12/stm32-spi.html
*	
*/



SPI_InitTypeDef SPI_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

uint8_t master_channel[SCREEN_WIDTH][LED_LEN][CHANNEL_DEPTH];
uint8_t frame_modified;
uint32_t LEDFrame[SCREEN_WIDTH][LED_LEN];

uint8_t current_col;
	
void APA102C_INIT(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; //SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	//SPI_InitStructure.SPI_CRCPolynomial = 10;

	SPI_Init(SPI1, &SPI_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

	/*-------- Configuring SCK, MISO, MOSI --------*/
	//SCK at PA5 MOSI at PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	

	SPI_Cmd(SPI1, ENABLE);
}

void sendByte(uint8_t byte)
{
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));  //transmit buffer empty?
	SPI_I2S_SendData(SPI1, byte); // send 8 bits of data
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY));
}

// Updates contents of Master Channel to LED Frame
void updateFrame(void)
{
	uint8_t col,row,r,g,b,br;
	uint32_t color;
	for(col = 0; col < SCREEN_WIDTH; col++){
		for(row = 0; row < LED_LEN; row++){
			r = master_channel[col][row][CH_RED];
			g = master_channel[col][row][CH_GREEN];
			b = master_channel[col][row][CH_BLUE];
			br = master_channel[col][row][CH_BRIGHTNESS];
			
			color = (0xE0 + br) << 24 | b << 16 | g << 8 | r;
			LEDFrame[col][row] = color;
		}
	}
}

//Display next column using global variable current_col
void displayNext(void)
{
		int i;
		//Start of Frame
		sendByte(0x00);
		sendByte(0x00);
		sendByte(0x00);
		sendByte(0x00);
		
		for (i =LED_LEN; i >= 0  ; i--)
		{
			sendByte(LEDFrame[current_col][i] >> 24); // INIT + GLOBAL
			sendByte(LEDFrame[current_col][i] >> 16); // BLUE
			sendByte(LEDFrame[current_col][i] >> 8); // GREEN
			sendByte(LEDFrame[current_col][i]); // RED
		}
		
		//End of Frame
		sendByte(0xff);
		//sendByte(0xff);
		//sendByte(0xff);
		//sendByte(0xff);

	current_col = (current_col + 1)  % SCREEN_WIDTH;
}


void getColor(uint32_t color_b,uint8_t color[], uint8_t size){
	color[CH_RED] = color_b;
	color[CH_BLUE] =color_b >>16; 
	color[CH_GREEN] = color_b >>8; 
	color[CH_BRIGHTNESS] = color_b >>24 ^ 0xE0; 
}


void setAllColorTest(void)
{
	int i,j;
	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		for(j = 0; j < LED_LEN; j++)
		{
			if(i==SCREEN_WIDTH-1){
			LEDFrame[i][j] = 0xefff0000;
			}
			else if (i == 0)
				{
				LEDFrame[i][j] = 0xef0000ff;
			}
		}
	}
}
