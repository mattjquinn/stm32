#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include "uart.h"

/*
 * MQUINN 06-21-2015 NOTE: The signature for these methods
 * differ from the ones provided by Geoffrey Brown in
 * "Discovering the STM32 Microcontroller", in that for each I have
 * eliminated the parameter allowing a variant USARTx to
 * be specified. Due to the differences in configuring the clocks
 * for USART1 vs. USARTs 2 and 3, it doesn't make sense to allow
 * this variant for this exercise, as only UART1 is needed.
 */

int uart_open(uint32_t baud, uint32_t flags) {

  // Initialize usart/gpio clocks.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |
                         RCC_APB2Periph_AFIO |
                         RCC_APB2Periph_GPIOA, ENABLE);

  // Configure usart pins
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_StructInit(&GPIO_InitStruct);

  // - Initialize USART1_TX
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // - Initialize USART1_RX
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Configure and enable the usart1
  USART_InitTypeDef USART_InitStructure;
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_Mode = flags;
  USART_Init(USART1, &USART_InitStructure);
  USART_Cmd(USART1, ENABLE);
}

int uart_close() {
  // MQUINN 06-21-2015: Exercise5-2 runs forever,
  // so no need to implement uart_close.
  return 0;
}

int uart_putc(int c) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART1->DR = (c & 0xff);
  return 0;
}

int uart_getc() {
  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
  return USART1->DR & 0xff;
}
