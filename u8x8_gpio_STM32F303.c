/*
 * u8x8_gpio_STM32F303.c
 *
 *  Created on: Jan 29, 2018
 *      Author: imashio
 */

#include "stm32f3xx_hal.h"
#include "u8g2.h"		// graphic display library

uint8_t u8x8_gpio_and_delay_STM32F303(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
    	break;							// can be used to setup pins
    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
		break;
    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
		break;
    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
    	delay_us(1);
		break;
    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
		HAL_Delay(1000);
		break;
    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
    	break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
    //case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
    case U8X8_MSG_GPIO_SPI_CLOCK:
    	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_4 ,arg_int );
    	break;
    //case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
    case U8X8_MSG_GPIO_SPI_DATA:
    	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_5 ,arg_int );
    	break;
    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
    	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_0 ,arg_int );
    	break;
    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
    	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_1 ,arg_int );
    	break;
    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
      break;							// arg_int=1: Input dir with pullup high for I2C clock pin
    case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
      break;							// arg_int=1: Input dir with pullup high for I2C data pin
    case U8X8_MSG_GPIO_MENU_SELECT:
      u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_NEXT:
      u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_PREV:
      u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
      break;
    case U8X8_MSG_GPIO_MENU_HOME:
      u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
      break;
    default:
      u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
  }
  return 1;
}
