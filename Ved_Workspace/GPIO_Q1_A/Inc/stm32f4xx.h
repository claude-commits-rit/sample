/*
 * stm32f4xx.h
 *
 *  Created on: Sep 20, 2026
 *      Author: desd
 */

#ifndef STM32F4XX_H_
#define STM32F4XX_H_


#include <stdint.h>

// Base addresses
#define RCC_BASE          0x40023800UL
#define GPIOD_BASE        0x40020C00UL
#define GPIOA_BASE        0x40020000UL

// Register Address Definitions
#define RCC_AHB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x30UL))
#define RCC_APB2ENR       (*(volatile uint32_t *)0x40021018)

#define GPIOD_MODER       (*(volatile uint32_t *)(GPIOD_BASE + 0x00UL))
#define GPIOD_ODR         (*(volatile uint32_t *)(GPIOD_BASE + 0x14UL))
#define GPIOA_MODER       (*(volatile uint32_t *)(GPIOA_BASE + 0x00UL))
#define GPIOA_IDR         (*(volatile uint32_t *)(GPIOA_BASE + 0x10UL))

#define SysTick_CTRL      (*(volatile uint32_t *)0xE000E010)
#define SysTick_LOAD      (*(volatile uint32_t *)0xE000E014)
#define SysTick_VAL       (*(volatile uint32_t *)0xE000E018)




void systick_init(void);
void delay_ms(uint32_t ms);
void toggle_green(void);
void toggle_all(void);
void forward_sequence(void);
void ForwardReverseSequence(void);
void ReadFromPin(void);


#endif /* STM32F4XX_H_ */
