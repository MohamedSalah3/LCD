/*
 * softwareDelay.c
 *
 * Created: 12/3/2019 6:40:01 PM
 *  Author: Amr
 */ 

#include "softwareDelay.h"

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the milli-seconds
 */
void SwDelay_ms(uint32_t n)
{
	uint8_t counter_256;
	uint8_t counter_21;
	while (n)
	{
		/* every 21 repetition of the 256 branches costs almost 1 milli second as: 48 micro x 21 = 1.008 milli second*/
		counter_21 = 21;
		while (counter_21)
		{
			/* every 256 branch costs 48 micro seconds */
			counter_256 = 255;
			while (counter_256)
			{
				counter_256--;
			}
			counter_21--;
		}
		n--;
	}
}

/**
 * Description: this delay function operate in a polling manner
 * 				don't use it with RTOSs
 * @param n: the micro-seconds
 */
void SwDelay_us(uint32_t n)
{
	while (n)
	{
		n--;
	}
}
