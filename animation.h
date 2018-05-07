
#ifndef ANIMATION_H_
#define ANIMATION_H_
#include "stm32f10x.h"
#include "stdint.h"
#include "TextDisplay.h"
#include "APA102C.h"
#include "sdcard/sdcard.h"

#define MAX_LAYER 10
#define BLOCK_SIZE            512 /* Block Size in Bytes */

#define NUMBER_OF_BLOCKS      16  /* For Multi Blocks operation (Read/Write) */
#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)   


extern uint8_t  Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
extern SD_Error Status;
extern SD_CardInfo SDCardInfo;	
//extern int i;
	
extern struct Param{
	uint8_t x;
	uint8_t y;
	
	uint8_t width;
	uint8_t height;
	
	uint8_t func_num;
	
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	uint8_t Brightness;
	
	uint8_t Red2;
	uint8_t Green2;
	uint8_t Blue2;
	uint8_t Brightness2;
	
	uint8_t cmd;
	uint8_t cmd2;
	char* text;
	double duration_fix;
	int  duration;
} Param;

struct Param textCenter(char* txt, int R, int G,int B);
struct Param bgColor(int R, int G, int B);
struct Param swipeColor(int R, int G, int B, int vertical, int direction, int duration);
struct Param putImage(int cmd, int width);
struct Param putStripe(int R , int G, int B, int R2, int G2, int B2, int width, int cmd);
void setAllColor(struct Param p);
void addLayer (struct Param p);
void removeLayer (int8_t index);
void updateAnimation(uint16_t period);
void callAnimation(struct Param p);
void stripe(struct Param p);
void swipe(struct Param p);
void checkers(struct Param p);
void circle(struct Param p);
void rect(struct Param p);
void image(struct Param p);
#endif
