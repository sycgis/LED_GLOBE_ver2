#ifndef ANIMATION_H_
#define ANIMATION_H_
#include "stm32f10x.h"
#include "stdint.h"
#include "USART.h"
#include "lcd.h"

void INITGPIO_OUT(void);
void INITGPIO_IN(void);
void INITGPIO_IN2(void);
int Check(void);
void ConvertToPitch(uint16_t button, uint16_t mode);

_Bool ButtonOn[17];

#endif
