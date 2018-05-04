#ifndef MAIN_H_
#define MAIN_H_

	#include "stm32f10x.h"
	#include "lcd.h"
	#include "math.h"
	#include "freq.h"
	#include "stdio.h"
	#include "animation.h"
	#include "APA102C.h"
	#include "TextDisplay.h"
	#include "MIDI.h"
	#include "LaunchKeys.h"
	#include "sdcard/sdcard.h"
	
	char freq_str[20];
	uint16_t oldv,period,oldfrequency;
	uint16_t freq;
	uint16_t hall_test;
	uint32_t sweep = 0xff000000;
	unsigned int delay, prev_delay, HIT;
	int     delay_offset;
	uint8_t pressed,pressed2;
	unsigned char  byte;




	void KEY_CONFIG(void);

	void update(uint8_t forceUpdate);
	void Delayus(int duration);
	void TIM2_IRQHandler(void);
	void Test(void);
	void LCD_TEST(void);
	void sd_test(void);
	
	void __attribute__((weak)) osa_mdelay(unsigned int msec);
	void __attribute__((weak)) delay_us(unsigned int usec);
	

  //SDCARD

#endif
