#define LED_LEN 32
#define SCREEN_WIDTH 32

#define CHANNEL_DEPTH 4
#define CH_RED 0
#define CH_GREEN 1
#define CH_BLUE 2 
#define CH_BRIGHTNESS 3

uint8_t master_channel[SCREEN_WIDTH][LED_LEN][CHANNEL_DEPTH];