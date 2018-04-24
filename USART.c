#include "USART.h"
#include "stm32f10x_usart.h"

//TX PB 10,  RX PB11 for USART3


void USART_INIT(void)
{
    USART_InitTypeDef usartConfig;
	  GPIO_InitTypeDef gpioConfig;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA ,ENABLE);


    usartConfig.USART_BaudRate = 115200; 
    usartConfig.USART_WordLength = USART_WordLength_8b; 
    usartConfig.USART_StopBits = USART_StopBits_1; 
    usartConfig.USART_Parity = USART_Parity_No;
    usartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &usartConfig);
	  USART_Cmd(USART1, ENABLE); 


    //PA9 = USART1.TX => Alternative Function Output
    gpioConfig.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioConfig.GPIO_Pin = GPIO_Pin_9;
    gpioConfig.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &gpioConfig);

    //PA10 = USART1.RX => Input
    gpioConfig.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpioConfig.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &gpioConfig);
}

void USARTsendByte(USART_TypeDef *USARTx, short  c)
{
	  USART_SendData(USARTx, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}


unsigned char USARTreadbyte(USART_TypeDef *USARTx)
{
    while ((USARTx->SR & USART_SR_RXNE) == RESET);
    return (unsigned char)USART_ReceiveData(USARTx);
}
void noteOn(uint8_t channel, uint8_t pitch, uint8_t velocity){
		uint8_t control = channel | 0x90;
		USARTsendByte(USART1,control);
	  USARTsendByte(USART1,pitch);
		USARTsendByte(USART1,velocity);
		//USARTsendByte(USART1,0x00);
}
void noteOff(uint8_t channel, uint8_t pitch, uint8_t velocity){
		uint8_t control = channel  | 0x80;
		USARTsendByte(USART1,control);
	  USARTsendByte(USART1,pitch);
		USARTsendByte(USART1,velocity);
		//USARTsendByte(USART1,0x00);
}