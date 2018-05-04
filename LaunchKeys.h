#ifndef LAUNCHKEYS_H_
#define LAUNCHKEYS_H_
#include "stm32f10x.h"
#include "stdint.h"
#include "MIDI.h"
#include "animation.h"

#define BUTTON_NUM 64
#define EFFECT_NUM 3
#define XOFF 10
#define YOFF 14

uint8_t mode;
void ANIMATION_INIT(void);
void INITGPIO_OUT(void);
void INITGPIO_IN(void);
void INITGPIO_IN2(void);
void INITGPIO_MODE(void);
uint16_t shiftBit(int shift);
int Check(void);
int modeCheck(void);
void ConvertToPitch(uint16_t button, uint16_t mode);


#endif
