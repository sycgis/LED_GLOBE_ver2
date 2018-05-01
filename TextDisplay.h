/*
 * TextDisplay.h
 *
 *  Created on: Mar 23, 2018
 *      Author: Yoon
 */

#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include "stm32f10x.h"
#include "animation.h"

extern struct Param info;

void getData(struct Param info);
void inputString(char* string,uint8_t Brightness, uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t xOffset, uint8_t yOffset);
void updateMaster(char character,uint8_t Brightness, uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t xOffset, uint8_t yOffset);
void writeOnMaster(int i, int j);
//void passInfo();
void drawLine(int starti, int startj, int length, int gradient);


//uint32_t makeBit(struct Param info);


#endif /* TEXTDISPLAY_H_ */
