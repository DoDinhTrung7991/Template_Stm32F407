/*
 * GPIO_header.h
 *
 *  Created on: Aug 23, 2022
 *      Author: trung97
 */

#ifndef INC_GPIO_HEADER_H_
#define INC_GPIO_HEADER_H_

#include <stdint.h>

typedef struct GPIOx_str
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIOx_t;

extern GPIOx_t *GPIOA_reg;
extern GPIOx_t *GPIOB_reg;
extern GPIOx_t *GPIOC_reg;
extern GPIOx_t *GPIOD_reg;
extern GPIOx_t *GPIOE_reg;
// GPIOx_t *GPIOA_reg = (GPIOx_t *)0x40020000;
// GPIOx_t *GPIOB_reg = (GPIOx_t *)0x40020400;
// GPIOx_t *GPIOC_reg = (GPIOx_t *)0x40020800;
// GPIOx_t *GPIOD_reg = (GPIOx_t *)0x40020C00;
// GPIOx_t *GPIOE_reg = (GPIOx_t *)0x40021000;

#endif /* INC_GPIO_HEADER_H_ */

