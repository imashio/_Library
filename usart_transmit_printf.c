/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "usart_transmit_printf.h"

#include "gpio.h"
#include "usart.h"


void USART_puts(USART_TypeDef* uartHandle,const char *s){
  HAL_UART_Transmit( uartHandle, s, strlen( s ), 50);
}


void HAL_UART_Transmit_printf(UART_HandleTypeDef* uartHandle, const char *format, ...) {
  va_list list;
  va_start(list, format);
  int len = vsnprintf(0, 0, format, list);
  char *s;
  s = (char *)malloc(len + 1);
  vsprintf(s, format, list);
  USART_puts(uartHandle, s);
  free(s);
  va_end(list);
  return;
}
