/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart2;

void USART_puts(USART_TypeDef* ,const char *);

void HAL_UART_Transmit_printf(UART_HandleTypeDef* , const char *, ...);
