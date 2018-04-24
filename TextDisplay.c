/*
 * TextDisplay.c
 *
 *  Created on: Mar 23, 2018
 *      Author: Yoon
 */

#include <stdio.h>
#include <string.h>
#include "TextDisplay.h"
#include "APA102C.h"
int last = 0;

/*
char A[12][16] =
{
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},//0000000000111111:1
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},//0000000111111111:2
		{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},//0000111111000000:3
		{0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0},//0011111001000000:4
		{0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0},//0111000001000000:5
		{1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},//1100000001000000:6
		{1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},//1100000001000000:6
		{0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0},//0111000001000000:5
		{0,0,1,1,1,1,1,0,0,1,0,0,0,0,0,0},//0011111001000000:4
		{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},//0000111111000000:3
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},//0000000111111111:2
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1} //0000000000111111:1		
};
char B[12][16] =
{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
		{0,1,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
		{0,1,1,1,1,1,0,0,1,0,0,0,0,0,1,1},
		{0,0,1,1,1,0,0,0,1,1,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
char C[12][16] =
{
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}
};
char D[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0}
};
char E[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1}
};
char F[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0}
};
char G[12][16] =
{
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,1,1,0,0,0,0,0,0,0,1,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}
};
char H[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
char I[12][16] =
{
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
};
char J[12][16] =
{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
char K[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
char L[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1}
};
char M[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
char N[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
char O[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
char P[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0}
};
char Q[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
char R[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,0},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1}
};
char S[12][16] =
{
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1}
};
char T[12][16] =
{
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
char U[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
char V[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0}
};
char W[12][16] =
{
		{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0}
};
char X[12][16] =
{
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
		{0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
		{0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
		{0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
};
char Y[12][16] =
{
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
char Z[12][16] =
{
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1},
		{1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1},
		{1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1},
};
*/





char A[5][6] = {
	{1,1,1,0,0,0},
	{0,0,1,1,1,0},
	{0,0,1,0,0,1},
	{0,0,1,1,1,0},
	{1,1,1,0,0,0}	
};

char B[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,1,0,1},
	{1,0,0,1,0,1},
	{0,1,1,0,1,0},	
};

char C[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,0,0,0,1},
	{1,0,0,0,0,1},
};

char D[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,0,0,0,1},
	{0,1,1,1,1,0},
};

char E[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,1,0,1},
	{1,0,0,1,0,1},
	{1,0,0,1,0,1}
};

char F[4][6] = {
	{1,1,1,1,1,1},
	{0,0,0,1,0,1},
	{0,0,0,1,0,1},
	{0,0,0,1,0,1}
};

char G[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,1,0,0,1},
	{1,1,1,0,0,1}
};

char H[4][6] = {
	{1,1,1,1,1,1},
	{0,0,1,0,0,0},
	{0,0,1,0,0,0},
	{1,1,1,1,1,1}
};

char I[3][6] = {
	{1,0,0,0,0,1},
	{1,1,1,1,1,1},
	{1,0,0,0,0,1}
};

char J[4][6] = {
	{1,1,0,0,0,1},
	{1,0,0,0,0,1},
	{1,1,1,1,1,1},
	{0,0,0,0,0,1}
};

char K[4][6] = {
	{1,1,1,1,1,1},
	{0,0,0,1,0,0},
	{0,0,1,0,1,0},
	{1,1,0,0,0,1}
};

char L[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,0},
	{1,0,0,0,0,0},
	{1,0,0,0,0,0}
};

char M[5][6] = {
	{1,1,1,1,1,1},
	{0,0,0,0,1,0},
	{0,0,0,1,0,0},
	{0,0,0,0,1,0},
	{1,1,1,1,1,1}
};

char N[5][6] = {
	{1,1,1,1,1,1},
	{0,0,0,0,1,0},
	{0,0,1,1,0,0},
	{0,1,0,0,0,0},
	{1,1,1,1,1,1}
};

char O[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,0,0,0,1},
	{1,1,1,1,1,1}
};

char P[4][6] = {
	{1,1,1,1,1,1},
	{0,0,0,1,0,1},
	{0,0,0,1,0,1},
	{0,0,0,1,1,1}
};

char Q[5][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,1,0,0,1},
	{1,1,1,1,1,1},
	{1,0,0,0,0,0}
};

char R[4][6] = {
	{1,1,1,1,1,1},
	{0,0,1,0,0,1},
	{0,0,1,0,0,1},
	{1,1,0,1,1,0}
};

char S[4][6] = {
	{1,0,1,1,1,1},
	{1,0,1,0,0,1},
	{1,0,1,0,0,1},
	{1,1,1,0,0,1}
};

char T[5][6] = {
	{0,0,0,0,0,1},
	{0,0,0,0,0,1},
	{1,1,1,1,1,1},
	{0,0,0,0,0,1},
	{0,0,0,0,0,1}
};

char U[4][6] = {
	{1,1,1,1,1,1},
	{1,0,0,0,0,0},
	{1,0,0,0,0,0},
	{1,1,1,1,1,1}
};

char V[4][6] = {
	{0,1,1,1,1,1},
	{1,0,0,0,0,0},
	{1,0,0,0,0,0},
	{0,1,1,1,1,1}
};

char W[5][6] = {
	{0,0,1,1,1,1},
	{1,1,0,0,0,0},
	{0,1,1,0,0,0},
	{1,1,0,0,0,0},
	{0,0,1,1,1,1}
};

char X[4][6] = {
	{1,1,0,0,1,1},
	{0,0,1,1,0,0},
	{0,0,1,1,0,0},
	{1,1,0,0,1,1}
};

char Y[3][6] = {
	{0,0,0,1,1,1},
	{1,1,1,0,0,0},
	{0,0,0,1,1,1}
};

char Z[4][6] = {
	{1,1,0,0,0,1},
	{1,0,1,0,0,1},
	{1,0,0,1,0,1},
	{1,0,0,0,1,1}
};


void getData(struct Param info)
{
	inputString(info.text, info.Brightness, info.Red, info.Green, info.Blue,info.y,info.x);	
}


void inputString(char* string, uint8_t Brightness, uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t xOffset, uint8_t yOffset){
	int i = 0;
	last = 0;
	while(string[i] != '\0'){
		updateMaster(string[i],Brightness, Red, Green, Blue, xOffset, yOffset);
		yOffset = 0;
		++i;
	}
}

void updateMaster(char character, uint8_t Brightness, uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t xOffset, uint8_t yOffset){
	int i;
	int j;
	if(last < 64){
		/*
		for(i = 0; i < xOffset; ++i){
			master_channel[j+last][i][CH_RED] = 0;
			master_channel[j+last][i][CH_GREEN] = 0;
			master_channel[j+last][i][CH_BLUE] = 0;
			master_channel[j+last][i][CH_BRIGHTNESS] = 0;
		}
		*/
		if(character == 'A'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 5 + yOffset; ++j){
					if(A[j-yOffset][i-xOffset] == 1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//Master[j-yOffset][i] = 0;
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'B'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(B[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'C'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(C[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//pprintf("\n");
			}
		}
		else if(character == 'D'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(D[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//pprintf("\n");
			}
		}
		else if(character == 'E'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(E[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//pprintf("\n");
			}
		}
		else if(character == 'F'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(F[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'G'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(G[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'H'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(H[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'I'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 3 + yOffset; ++j){
					if(I[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'J'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(J[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'K'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(K[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'L'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(L[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'M'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 5 + yOffset; ++j){
					if(M[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'N'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 5 + yOffset; ++j){
					if(N[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'O'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(O[j-yOffset][i-xOffset] ==1){
						////Master[j+last][i] = 1;
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
						//printf("#");
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'P'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(P[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'Q'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 5 + yOffset; ++j){
					if(Q[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'R'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(R[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'S'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(S[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'T'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(T[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'U'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(U[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'V'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(V[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'W'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 5 + yOffset; ++j){
					if(W[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'X'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(X[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'Y'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 3 + yOffset; ++j){
					if(Y[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == 'Z'){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = yOffset; j < 4 + yOffset; ++j){
					if(Z[j-yOffset][i-xOffset] ==1){
						//Master[j+last][i] = 1;
						//printf("#");
						master_channel[j+last][i][CH_RED] = Red;
						master_channel[j+last][i][CH_GREEN] = Green;
						master_channel[j+last][i][CH_BLUE] = Blue;
						master_channel[j+last][i][CH_BRIGHTNESS] = Brightness;
					}
					else{
						//printf(".");
					}
				}
				//printf("\n");
			}
		}
		else if(character == ' '){
			for(i = xOffset; i < 6+xOffset; ++i){
				for(j = 0; j < 2; ++j){
					/*
					master_channel[j+last][i][CH_RED] = 0;
					master_channel[j+last][i][CH_GREEN] = 0;
					master_channel[j+last][i][CH_BLUE] = 0;
					master_channel[j+last][i][CH_BRIGHTNESS] = 0;
					*/
				}
				//printf("\n");
			}
		}
	last += j;
	//printf("%d",last);
	}
}