/**
*   Reference: https://github.com/FabLabSeoul/WingProject/wiki/STM32-UART
**/
#ifndef  USART_H_
#define USART_H_

#include "stm32f10x.h"

void USART_INIT(void);

unsigned char USARTreadByte(USART_TypeDef *USARTx);
void USARTsendByte(USART_TypeDef *USARTx, short  c);
void noteOn(uint8_t channel, uint8_t pitch, uint8_t velocity);
void noteOff(uint8_t channel, uint8_t pitch, uint8_t velocity);
#endif /* USART_H_ */
