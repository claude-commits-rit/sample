/*
 * LedDisplay.c
 *
 *  Created on: Oct 7, 2026
 *      Author: sande
 */

#include "LedDisplay.h"


void LED_Display(uint8_t LED_Status_No){

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, LED_Status_No == 0x01);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, LED_Status_No == 0x02);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, LED_Status_No == 0x03);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, LED_Status_No == 0x04);
}
