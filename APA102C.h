#include "stm32f10x.h"


#define LED_LEN 36
#define SCREEN_WIDTH 52

#define CHANNEL_DEPTH 4
#define CH_RED 0
#define CH_GREEN 1
#define CH_BLUE 2 
#define CH_BRIGHTNESS 3

#define TRUE 1
#define FALSE 0

#define RED_b 0xff0000ff
#define GREEN_b 0xff00ff00
#define BLUE_b 0xffff0000

extern uint8_t master_channel[SCREEN_WIDTH][LED_LEN][CHANNEL_DEPTH];
extern uint8_t frame_modified;
extern uint8_t current_col;
	
void APA102C_INIT(void);
void sendByte(uint8_t byte);
void updateFrame(void);
void displayNext(void);
void setAllColor(uint8_t R, uint8_t G, uint8_t B, uint8_t Br);
void setAllColorTest(void);
uint32_t color(uint8_t R, uint8_t G, uint8_t B, uint8_t Br);
void getColor(uint32_t color_b,uint8_t color[], uint8_t size);
