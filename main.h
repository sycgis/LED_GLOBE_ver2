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
	unsigned int delay;
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
	
	typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

  //SDCARD
	#define BLOCK_SIZE            512 /* Block Size in Bytes */

	#define NUMBER_OF_BLOCKS      13  /* For Multi Blocks operation (Read/Write) */
	#define MULTI_BUFFER_SIZE    (BLOCK_SIZE * NUMBER_OF_BLOCKS)   


	uint8_t  Buffer_Block_Rx[BLOCK_SIZE];
	uint8_t readbuff[BLOCK_SIZE];
	uint8_t  Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];
	volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
	SD_Error Status = SD_OK;
	extern SD_CardInfo SDCardInfo;	
	int i;
	 

	void SD_SingleBlockTest(void);
	void SD_MultiBlockTest(void);
	void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t Offset);
	TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);
	TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength);

	
void SD_SingleBlockTest(void)
{  
  if (Status == SD_OK)
  {
    /* Read block of 512 bytes from address 0 */
    Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  if(TransferStatus1 == PASSED)
   LCD_DrawString(0,0, "PASSED");		
 
  else  
    LCD_DrawString(0,0, "FAILED"); 
}

void SD_MultiBlockTest(void)
{

  if (Status == SD_OK)
  {
    /* Read block of many bytes from address 0 */
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x100A036, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }

  if(TransferStatus2 == PASSED)	  
  	LCD_DrawString(50,0, "PASSED");

  else 
  	LCD_DrawString(50,0, "FAILED");

}
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return PASSED;
}


TestStatus eBuffercmp(uint8_t* pBuffer, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    /* In some SD Cards the erased state is 0xFF, in others it's 0x00 */
    if ((*pBuffer != 0xFF) && (*pBuffer != 0x00))
    {
      return FAILED;
    }

    pBuffer++;
  }

  return PASSED;
}

#endif
