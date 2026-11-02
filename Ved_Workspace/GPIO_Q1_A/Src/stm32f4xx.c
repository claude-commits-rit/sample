/*
 * stm32f4xx.c
 *
 *  Created on: Sep 20, 2026
 *      Author: desd
 */


#include "stm32f4xx.h"

void systick_init(void)
{
    SysTick_LOAD = 15999;                    /* 16 MHz → 1 ms tick */
    SysTick_VAL  = 0;
    SysTick_CTRL = (1 << 2) | (1 << 0);      /* CLKSOURCE=1, ENABLE=1 */
}

void delay_ms(uint32_t ms)
{
	uint32_t count = 0;
	uint32_t prev  = SysTick_VAL;

	for (;;)
	{
	    uint32_t now = SysTick_VAL;
	    if (now > prev) count++;   /* wrapped: 15999 → 0 */
		prev = now;
		if (count >= ms) break;
	}
}

// Q1. Configure PD12 as a GPIO output and continuously toggle the green on board LED with a 500ms delay.

void toggle_green(void)
{
	systick_init();

	RCC_AHB1ENR |= (1 << 3);


	GPIOD_MODER |= (1 << 24 );
	GPIOD_MODER &= ~(1 << 25);

	GPIOD_ODR |= (1 << 12);
	delay_ms(500);
	GPIOD_ODR &= ~(1 << 12);
	delay_ms(500);

}

// Q2. Configure PD12 - PD15 as outputs and switch all four onboard LEDs ON and OFF simultaneously.

void toggle_all(void)
{
	systick_init();

	RCC_AHB1ENR |= (1 << 3);


	GPIOD_MODER |= (1 << 24 | 1 << 26 | 1 << 28 | 1 << 30 );
	GPIOD_MODER &= ~(1 << 25 | 1 << 27 | 1 << 29 | 1 << 31);

	GPIOD_ODR |= (1 << 12 | 1 << 13 | 1 << 14 | 1 << 15);
	delay_ms(500);
	GPIOD_ODR &= ~(1 << 12 | 1 << 13 | 1 << 14 | 1 << 15);
	delay_ms(500);

}

// Q3. Create a forward LED sequence from PD12 - PD15 with each LED ON for 500ms.

void forward_sequence(void)
{
	systick_init();

	RCC_AHB1ENR |= (1 << 3);


	GPIOD_MODER |= (1 << 24 | 1 << 26 | 1 << 28 | 1 << 30 );
	GPIOD_MODER &= ~(1 << 25 | 1 << 27 | 1 << 29 | 1 << 31);

	GPIOD_ODR |= (1 << 12);
	delay_ms(500);
	GPIOD_ODR |= (1 << 13);
	delay_ms(500);
	GPIOD_ODR |= (1 << 14);
	delay_ms(500);
	GPIOD_ODR |= (1 << 15);
	delay_ms(500);

	GPIOD_ODR &= ~(1 << 12);
	delay_ms(500);
	GPIOD_ODR &= ~(1 << 13);
	delay_ms(500);
	GPIOD_ODR &= ~(1 << 14);
	delay_ms(500);
	GPIOD_ODR &= ~(1 << 15);
	delay_ms(500);

}

//Q4. Create a forward and reverse LED running pattern using PD12 - PD15.

void ForwardReverseSequence(void)
{
	systick_init();

	RCC_AHB1ENR |= (1 << 3);

	GPIOD_MODER |= (1 << 24 | 1 << 26 | 1 << 28 | 1 << 30 );
	GPIOD_MODER &= ~(1 << 25 | 1 << 27 | 1 << 29 | 1 << 31);

	const uint16_t LedSequence[7] = {
			(1 << 12),
			(1 << 13),
			(1 << 14),
			(1 << 15),
			(1 << 14),
			(1 << 13),
			(1 << 12)
	};

	static uint8_t step = 0;

	GPIOD_ODR &= ~(0x000F << 12);

	GPIOD_ODR |=  LedSequence[step];

	step++;

	if(step >= 7)
	{
		step = 0;
	}
}


//Q5.Configure PA0 as a GPIO input and make PD12 remain ON only while the user button is pressed.

void ReadFromPin(void)
{

	RCC_AHB1ENR |= (1 << 3 | 1 << 0);

	GPIOD_MODER &= ~(0x3 << (12 * 2));
	GPIOD_MODER |=  (0x1 << (12 * 2));

    GPIOA_MODER &= ~(1 << 0);
    GPIOA_MODER &= ~(1 << 1);

    if(GPIOA_IDR & (1 << 0))
    {
    	GPIOD_ODR |= (1 << 12);
    }
    else
    {
    	GPIOD_ODR &= ~(1 << 12);
    }
}
