/*
 * u8x8_byte_4wire_hw_spi.c
 *
 *  Created on: Feb 5, 2018
 *      Author: imashio
 */

#include "stm32f3xx_hal.h"
#include "spi.h"
#include "u8g2.h"		// graphic display library


uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t byte;
	uint8_t *data;

	switch(msg){

		case U8X8_MSG_BYTE_SEND:
			data = (uint8_t *)arg_ptr;
			while( arg_int > 0 ){
				byte = *data;
				data++;
				arg_int--;
				HAL_SPI_Transmit(&hspi1, &byte, 1, 10);
			}
			break;

		case U8X8_MSG_BYTE_START_TRANSFER:	 // set CS to 0
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
			break;

		case U8X8_MSG_BYTE_END_TRANSFER:	 // set CS to 1
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
			break;

		case U8X8_MSG_BYTE_SET_DC: // DC
			if (arg_int){
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
			}else{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
			}
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, arg_int);
			break;

		default:
			return 0;

	}
	return 1;
}

