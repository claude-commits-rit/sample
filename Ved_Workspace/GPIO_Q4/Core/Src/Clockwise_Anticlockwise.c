/*
 * Clockwise_Anticlockwise.c
 *
 *  Created on: Sep 22, 2026
 *      Author: sande
 */

#include "stm32f4xx_hal.h"
#include "Clockwise_Anticlockwise.h"

const uint16_t LedSequence[7] = {
			(1 << 12),
			(1 << 13),
			(1 << 14),
			(1 << 15),
			(1 << 14),
			(1 << 13),
			(1 << 12)
};

void forwardReverse(void)
{
	static uint8_t step = 0;

	HAL_GPIO_WritePin(GPIOD, LedSequence[step], GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOD, LedSequence[step], GPIO_PIN_RESET);
	HAL_Delay(500);

	step++;

	if(step >= 7)
	{
		step = 0;
	}
}
