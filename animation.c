#include "animation.h"
#include "stdio.h"
#include "lcd.h"

char debug[20];

struct Param animation_layer[MAX_LAYER];
SD_Error Status = SD_OK;
uint8_t Buffer_MultiBlock_Rx[MULTI_BUFFER_SIZE];

void drawPoint(int i, int j, int R, int G, int B,int Br){
			master_channel[i][j][CH_RED] = R;
			master_channel[i][j][CH_GREEN] = G;
			master_channel[i][j][CH_BLUE] = B;
			master_channel[i][j][CH_BRIGHTNESS] = Br;
}
void drawStripe(int index, int start, int end, int length, int vertical, int R, int G, int B, int Brightness){
		uint8_t i;
	
	for(i=start;i < end; i++){
					if(vertical){
					drawPoint(index,i,R,G,B,Brightness);
					}
					else{
					drawPoint(i,index,R,G,B,Brightness);	
					}
				}
}
void drawCircle ( uint16_t usC, uint16_t usP, uint16_t radius, int R, int G, int B, int Br,int thickness)
{	
	int centerC = usC+radius;
	int centerP = usP+radius;
	int i,j,r,distance;
	r = radius;
	if(usC + 2* radius >= SCREEN_WIDTH || usP + 2*radius >= LED_LEN){
		return;
	}
	for(i = usC; i <= usC+ 2*radius; i++){
		for(j = usP; j <= usP+ 2*radius;j++){
			distance = r*r-(centerC-i)*(centerC-i)-(centerP-j)*(centerP-j);
			if( distance < thickness && distance > -thickness) drawPoint(i,j,R,G,B,Br);
		}
	}
	
}
uint8_t animation_layer_length;
//Adds the animation to the array, ignores it if the array is full.
void addLayer(struct Param layer)
{
	if(animation_layer_length < MAX_LAYER - 1 )
	{
		animation_layer[animation_layer_length] = layer;
		
		animation_layer_length++;
	}
}

//Removes the layer in the array. If index is negative, remove last element.
void removeLayer(int8_t index)
{
	int i;
	if(index < 0 ) animation_layer_length--;
	else{
		for(i = index; i < animation_layer_length - 1; i++)
		{
			animation_layer[i] = animation_layer[i+1];
		}
		animation_layer_length--;
	}
}


// Calls animation depending on the funcition number. Add additional animation as we develop it
void callAnimation(struct Param p)
{
	switch (p.func_num)
	{
		case 0:
			getData(p);
			break;
		case 1:
			stripe(p);
		  break;
		case 2:
			swipe(p);
		  break;
		case 3:
			circle(p);
		  break;
		case 4:
			setAllColor(p);
			break;
		case 5:
			image(p);
			break;
	}
}
//Sets LED Frame to a single color
void setAllColor(struct Param p)
{
	int i,j;
	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		for(j = 0; j < LED_LEN; j++)
		{

			master_channel[i][j][CH_RED] = p.Red;
			master_channel[i][j][CH_GREEN] = p.Green;
			master_channel[i][j][CH_BLUE] = p.Blue;
			master_channel[i][j][CH_BRIGHTNESS] = p.Brightness;
			
		}
	}
}

//Loops through all the animation layer and clears it.
void updateAnimation(uint16_t period)
{
	uint8_t i;
	for(i=0;i<animation_layer_length;i++)
	{
		animation_layer[i].duration -= period; // in ms.
		callAnimation(animation_layer[i]);	
		if(animation_layer[i].duration <= 0) removeLayer(i);
	}
  if(animation_layer_length>0){
	updateFrame();
	}
}

void stripe(struct Param p){
 uint8_t stripe_width = SCREEN_WIDTH/p.cmd;
 uint8_t vertical = p.cmd2;
 uint8_t on = FALSE;
 uint8_t i_len, end;
  int i;
	
	if (vertical){
		i_len = SCREEN_WIDTH;
		end = LED_LEN;
	}
	else {
		i_len = LED_LEN;
		end = SCREEN_WIDTH;
	}

	for(i=0;i<i_len;i++){
			if(i % stripe_width == 0) on = !on;
			if(on){
				drawStripe(i, 0 , end, end, vertical,p.Red,p.Green,p.Blue,p.Brightness);
			}
			else{
				drawStripe(i, 0 , end, end, vertical,p.Red2,p.Green2,p.Blue2,p.Brightness2);
			}
		}
	
}
void swipe(struct Param p){
	uint8_t vertical = p.cmd;
	uint8_t direction = p.cmd2;
	uint8_t i,i_len,end;
	int index;
	if(vertical){
		i_len = SCREEN_WIDTH;
		end = LED_LEN;
	}
	else{
		i_len = LED_LEN;
		end = SCREEN_WIDTH;
	}
	if(p.duration < 0) p.duration = 0;
	index = (1- p.duration/p.duration_fix) * i_len;
	
	
	if(direction){
		for(i = 0; i < index; i++){
			drawStripe(i, 0,  end , end, vertical, p.Red, p.Green, p.Blue, p.Brightness);
		}
	}
	else{
		for(i = i_len-1; i > i_len - index; i--){
			drawStripe(i, 0,  end, end, vertical, p.Red, p.Green, p.Blue, p.Brightness);
		}
	}
	
}

void circle(struct Param p){
	uint16_t radius, i,j;
	i = p.x;
	j = p.y;
	radius = p.width;
	drawCircle ( i, j, radius,  p.Red, p.Green, p.Blue, p.Brightness,p.cmd);
}

void image(struct Param p){
		int i,j,k;
		unsigned int address = 0x1008036;
		address += 0x2000 * p.cmd;
	  if (Status == SD_OK)
  {
    /* Read block of many bytes from address 0 */
    Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, address, BLOCK_SIZE, NUMBER_OF_BLOCKS);
    /* Check if the Transfer is finished */
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
  }
	

		k = 54;
		for (j = LED_LEN -1 ; j >= 0; j--)
	{
		for(i = 0; i < p.y; i++)
		{
			if(k + 3<LED_LEN*p.y*CHANNEL_DEPTH){
			master_channel[i][j][CH_RED] = Buffer_MultiBlock_Rx[k+2];
			master_channel[i][j][CH_GREEN] = Buffer_MultiBlock_Rx[k+1];
			master_channel[i][j][CH_BLUE]= Buffer_MultiBlock_Rx[k];
			k+=3;
			if(i == p.y-1) k += (p.y *3)%4;
			}
			}
		}
}
struct Param putImage(int cmd,int width){
	struct Param x;

	x.func_num = 5;
	x.cmd = cmd;
	x.y = width;
	
	return x;
}
struct Param textCenter(char* txt, int R, int G, int B){
	struct Param x;
	x.x = 10;
	x.y =14;
	x.func_num = 0;
	x.Red = R;
	x.Green = G;
	x.Blue = B;
	x.text = txt;
	
	
	return x;
}

struct Param bgColor(int R, int G, int B){
	struct Param x;
	x.func_num = 4;
	x.Red = R;
	x.Green = G;
	x.Blue = B;

	return x;
}

struct Param swipeColor(int R, int G, int B, int vertical, int direction, int duration){
	struct Param x;
	x.func_num = 2;
	x.Red = R;
	x.Green = G;
	x.Blue = B;
	x.cmd = vertical;
	x.cmd2 = direction;
	x.duration = duration;
	x.duration_fix = duration;
	
	return x;
}
