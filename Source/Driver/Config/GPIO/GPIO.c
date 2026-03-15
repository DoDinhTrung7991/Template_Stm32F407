#include "GPIO.h"
#include "bit_operator.h"

GPIOx_t *GPIOA_reg = (GPIOx_t *)0x40020000;
GPIOx_t *GPIOB_reg = (GPIOx_t *)0x40020400;
GPIOx_t *GPIOC_reg = (GPIOx_t *)0x40020800;
GPIOx_t *GPIOD_reg = (GPIOx_t *)0x40020C00;
GPIOx_t *GPIOE_reg = (GPIOx_t *)0x40021000;
bool GPIOx_IN_getVal_check_b = OK;

static void GPIO_init(GPIO_ENABLE_t GPIOxEN);

bool GPIO_IN_setup(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, GPIO_pullDir_t pullDir_en)
{
	bool returnVal = OK;
	
	if (15U < pos_u8)
	{
		returnVal = NOT_OK;
		return returnVal;
	}
	else
	{
		switch (GPIOx_en)
		{
			case GPIOAEN:
				GPIO_init(GPIOAEN);
				WRITE_REG(GPIOA_reg->MODER, 3UL, (pos_u8 * 2), 0UL);
				switch (pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOA_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOA_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOA_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;

			case GPIOEEN:
				GPIO_init(GPIOEEN);
				WRITE_REG(GPIOE_reg->MODER, 3UL, (pos_u8 * 2), 0UL);
				switch (pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOE_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOE_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOE_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;
			
			default:
				returnVal = NOT_OK;
				break;
		}
	}

	return returnVal;
}

bool GPIO_IN_getVal(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8)
{
	bool GPIO_IN_val_b = 0;

	if (15U < pos_u8)
	{
		GPIOx_IN_getVal_check_b = NOT_OK;
		return GPIOx_IN_getVal_check_b;
	}
	else
	{
		GPIOx_IN_getVal_check_b = OK;
	}

	switch (GPIOx_en)
	{
		case GPIOAEN:
			GPIO_IN_val_b = READ_REG(GPIOA_reg->IDR, 1UL, pos_u8);
			break;
		case GPIOEEN:
			GPIO_IN_val_b = READ_REG(GPIOE_reg->IDR, 1UL, pos_u8);
			break;
		default:
			break;
	}

	return GPIO_IN_val_b;
}

bool GPIO_OUT_setup(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, GPIO_purpose_t GPIO_purpose_en, AFRx_t AFx_en, GPIO_outputType_t GPIO_outputType_en, GPIO_pullDir_t GPIO_pullDir_en)
{
	bool returnVal = OK;

	if (15U < pos_u8)
	{
		returnVal = NOT_OK;
		return returnVal;
	}
	else
	{
		switch (GPIOx_en)
		{
			case GPIOAEN:
				GPIO_init(GPIOAEN);
				switch (GPIO_purpose_en)
				{
					case GP:
						WRITE_REG(GPIOA_reg->MODER, 3UL, (pos_u8 * 2U), 1UL);
						break;
					case AF:
						WRITE_REG(GPIOA_reg->MODER, 3UL, (pos_u8 * 2U), 2UL);
						switch (AFx_en)
						{
							case AF0:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOA_reg->AFRL, 0xFUL, (pos_u8 * 4U), 0UL);
								}
								else
								{
									WRITE_REG(GPIOA_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 0UL);
								}							
								break;

							case AF1:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOA_reg->AFRL, 0xFUL, (pos_u8 * 4U), 1UL);
								}
								else
								{
									WRITE_REG(GPIOA_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 1UL);
								}							
								break;

							case AF2:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOA_reg->AFRL, 0xFUL, (pos_u8 * 4U), 2UL);
								}
								else
								{
									WRITE_REG(GPIOA_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 2UL);
								}							
								break;

							case AF3:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOA_reg->AFRL, 0xFUL, (pos_u8 * 4U), 3UL);
								}
								else
								{
									WRITE_REG(GPIOA_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 3UL);
								}							
								break;

							case AF7:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOA_reg->AFRL, 0xFUL, (pos_u8 * 4U), 7UL);
								}
								else
								{
									WRITE_REG(GPIOA_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 7UL);
								}							
								break;

							case AF9:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOA_reg->AFRL, 0xFUL, (pos_u8 * 4U), 9UL);
								}
								else
								{
									WRITE_REG(GPIOA_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 9UL);
								}							
								break;

							default:
								returnVal = NOT_OK;
								break;
						}
						break;
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_outputType_en)
				{
					case PP:
						WRITE_REG(GPIOA_reg->OTYPER, 1UL, pos_u8, 0UL);
						break;
					
					case OD:
						WRITE_REG(GPIOA_reg->OTYPER, 1UL, pos_u8, 1UL);
						break;
					
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOA_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOA_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOA_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;

			case GPIOBEN:
				GPIO_init(GPIOBEN);
				switch (GPIO_purpose_en)
				{
					case GP:
						WRITE_REG(GPIOB_reg->MODER, 3UL, (pos_u8 * 2U), 1UL);
						break;
					case AF:
						WRITE_REG(GPIOB_reg->MODER, 3UL, (pos_u8 * 2U), 2UL);
						switch (AFx_en)
						{
							case AF0:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOB_reg->AFRL, 0xFUL, (pos_u8 * 4U), 0UL);
								}
								else
								{
									WRITE_REG(GPIOB_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 0UL);
								}							
								break;

							case AF1:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOB_reg->AFRL, 0xFUL, (pos_u8 * 4U), 1UL);
								}
								else
								{
									WRITE_REG(GPIOB_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 1UL);
								}							
								break;

							case AF2:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOB_reg->AFRL, 0xFUL, (pos_u8 * 4U), 2UL);
								}
								else
								{
									WRITE_REG(GPIOB_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 2UL);
								}							
								break;

							case AF3:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOB_reg->AFRL, 0xFUL, (pos_u8 * 4U), 3UL);
								}
								else
								{
									WRITE_REG(GPIOB_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 3UL);
								}							
								break;

							case AF7:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOB_reg->AFRL, 0xFUL, (pos_u8 * 4U), 7UL);
								}
								else
								{
									WRITE_REG(GPIOB_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 7UL);
								}							
								break;

							case AF9:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOB_reg->AFRL, 0xFUL, (pos_u8 * 4U), 9UL);
								}
								else
								{
									WRITE_REG(GPIOB_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 9UL);
								}							
								break;

							default:
								returnVal = NOT_OK;
								break;
						}
						break;
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_outputType_en)
				{
					case PP:
						WRITE_REG(GPIOB_reg->OTYPER, 1UL, pos_u8, 0UL);
						break;
					
					case OD:
						WRITE_REG(GPIOB_reg->OTYPER, 1UL, pos_u8, 1UL);
						break;
					
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOB_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOB_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOB_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;

			case GPIOCEN:
				GPIO_init(GPIOCEN);
				switch (GPIO_purpose_en)
				{
					case GP:
						WRITE_REG(GPIOC_reg->MODER, 3UL, (pos_u8 * 2U), 1UL);
						break;
					case AF:
						WRITE_REG(GPIOC_reg->MODER, 3UL, (pos_u8 * 2U), 2UL);
						switch (AFx_en)
						{
							case AF0:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOC_reg->AFRL, 0xFUL, (pos_u8 * 4U), 0UL);
								}
								else
								{
									WRITE_REG(GPIOC_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 0UL);
								}							
								break;

							case AF1:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOC_reg->AFRL, 0xFUL, (pos_u8 * 4U), 1UL);
								}
								else
								{
									WRITE_REG(GPIOC_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 1UL);
								}							
								break;

							case AF2:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOC_reg->AFRL, 0xFUL, (pos_u8 * 4U), 2UL);
								}
								else
								{
									WRITE_REG(GPIOC_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 2UL);
								}							
								break;

							case AF3:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOC_reg->AFRL, 0xFUL, (pos_u8 * 4U), 3UL);
								}
								else
								{
									WRITE_REG(GPIOC_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 3UL);
								}							
								break;

							case AF7:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOC_reg->AFRL, 0xFUL, (pos_u8 * 4U), 7UL);
								}
								else
								{
									WRITE_REG(GPIOC_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 7UL);
								}							
								break;

							case AF9:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOC_reg->AFRL, 0xFUL, (pos_u8 * 4U), 9UL);
								}
								else
								{
									WRITE_REG(GPIOC_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 9UL);
								}							
								break;

							default:
								returnVal = NOT_OK;
								break;
						}
						break;
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_outputType_en)
				{
					case PP:
						WRITE_REG(GPIOC_reg->OTYPER, 1UL, pos_u8, 0UL);
						break;
					
					case OD:
						WRITE_REG(GPIOC_reg->OTYPER, 1UL, pos_u8, 1UL);
						break;
					
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOC_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOC_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOC_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;

			case GPIODEN:
				GPIO_init(GPIODEN);
				switch (GPIO_purpose_en)
				{
					case GP:
						WRITE_REG(GPIOD_reg->MODER, 3UL, (pos_u8 * 2U), 1UL);
						break;
					case AF:
						WRITE_REG(GPIOD_reg->MODER, 3UL, (pos_u8 * 2U), 2UL);
						switch (AFx_en)
						{
							case AF0:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOD_reg->AFRL, 0xFUL, (pos_u8 * 4U), 0UL);
								}
								else
								{
									WRITE_REG(GPIOD_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 0UL);
								}							
								break;

							case AF1:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOD_reg->AFRL, 0xFUL, (pos_u8 * 4U), 1UL);
								}
								else
								{
									WRITE_REG(GPIOD_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 1UL);
								}							
								break;

							case AF2:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOD_reg->AFRL, 0xFUL, (pos_u8 * 4U), 2UL);
								}
								else
								{
									WRITE_REG(GPIOD_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 2UL);
								}							
								break;

							case AF3:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOD_reg->AFRL, 0xFUL, (pos_u8 * 4U), 3UL);
								}
								else
								{
									WRITE_REG(GPIOD_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 3UL);
								}							
								break;

							case AF7:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOD_reg->AFRL, 0xFUL, (pos_u8 * 4U), 7UL);
								}
								else
								{
									WRITE_REG(GPIOD_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 7UL);
								}							
								break;

							case AF9:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOD_reg->AFRL, 0xFUL, (pos_u8 * 4U), 9UL);
								}
								else
								{
									WRITE_REG(GPIOD_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 9UL);
								}							
								break;

							default:
								returnVal = NOT_OK;
								break;
						}
						break;
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_outputType_en)
				{
					case PP:
						WRITE_REG(GPIOD_reg->OTYPER, 1UL, pos_u8, 0UL);
						break;
					
					case OD:
						WRITE_REG(GPIOD_reg->OTYPER, 1UL, pos_u8, 1UL);
						break;
					
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOD_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOD_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOD_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;

			case GPIOEEN:
				GPIO_init(GPIOEEN);
				switch (GPIO_purpose_en)
				{
					case GP:
						WRITE_REG(GPIOE_reg->MODER, 3UL, (pos_u8 * 2U), 1UL);
						break;
					case AF:
						WRITE_REG(GPIOE_reg->MODER, 3UL, (pos_u8 * 2U), 2UL);
						switch (AFx_en)
						{
							case AF0:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOE_reg->AFRL, 0xFUL, (pos_u8 * 4U), 0UL);
								}
								else
								{
									WRITE_REG(GPIOE_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 0UL);
								}							
								break;

							case AF1:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOE_reg->AFRL, 0xFUL, (pos_u8 * 4U), 1UL);
								}
								else
								{
									WRITE_REG(GPIOE_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 1UL);
								}							
								break;

							case AF2:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOE_reg->AFRL, 0xFUL, (pos_u8 * 4U), 2UL);
								}
								else
								{
									WRITE_REG(GPIOE_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 2UL);
								}							
								break;

							case AF3:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOE_reg->AFRL, 0xFUL, (pos_u8 * 4U), 3UL);
								}
								else
								{
									WRITE_REG(GPIOE_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 3UL);
								}							
								break;

							case AF7:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOE_reg->AFRL, 0xFUL, (pos_u8 * 4U), 7UL);
								}
								else
								{
									WRITE_REG(GPIOE_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 7UL);
								}							
								break;

							case AF9:
								if (7 >= pos_u8)
								{
									WRITE_REG(GPIOE_reg->AFRL, 0xFUL, (pos_u8 * 4U), 9UL);
								}
								else
								{
									WRITE_REG(GPIOE_reg->AFRH, 0xFUL, ((pos_u8 - 8U) * 4U), 9UL);
								}							
								break;

							default:
								returnVal = NOT_OK;
								break;
						}
						break;
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_outputType_en)
				{
					case PP:
						WRITE_REG(GPIOE_reg->OTYPER, 1UL, pos_u8, 0UL);
						break;
					
					case OD:
						WRITE_REG(GPIOE_reg->OTYPER, 1UL, pos_u8, 1UL);
						break;
					
					default:
						returnVal = NOT_OK;
						break;
				}

				switch (GPIO_pullDir_en)
				{
					case PU:
						WRITE_REG(GPIOE_reg->PUPDR, 3UL, (pos_u8 * 2), 1UL);
						break;
					case PD:
						WRITE_REG(GPIOE_reg->PUPDR, 3UL, (pos_u8 * 2), 2UL);
						break;
					case NoP:
						WRITE_REG(GPIOE_reg->PUPDR, 3UL, (pos_u8 * 2), 0UL);
						break;
					default:
						returnVal = NOT_OK;
						break;
				}
				break;

			default:
				returnVal = NOT_OK;
				break;
		}
	}
	
	return returnVal;
}

bool GPIO_OUT_setVal(GPIO_ENABLE_t GPIOx_en, uint8_t pos_u8, bool setVal_b)
{
	bool returnVal = OK;

	if (15U < pos_u8)
	{
		returnVal = NOT_OK;
		return returnVal;
	}

	switch (GPIOx_en)
	{
		case GPIOAEN:
			if (1 == setVal_b)
			{
				WRITE_REG(GPIOA_reg->ODR, 1UL, pos_u8, 1);
			}
			else
			{
				WRITE_REG(GPIOA_reg->ODR, 1UL, pos_u8, 0);
			}	
			break;

		case GPIOEEN:
			if (1 == setVal_b)
			{
				WRITE_REG(GPIOE_reg->ODR, 1UL, pos_u8, 1);
			}
			else
			{
				WRITE_REG(GPIOE_reg->ODR, 1UL, pos_u8, 0);
			}
			break;

		default:
			returnVal = NOT_OK;
			break;
	}

	return returnVal;
}

static void GPIO_init(GPIO_ENABLE_t GPIOxEN)
{
	SET_BIT(RCC_reg->AHB1ENR, GPIOxEN);
}
