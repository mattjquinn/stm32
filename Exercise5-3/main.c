#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include "uart.h"

void Delay(uint32_t nTime);

main() {
  // Iniialize timer tick.
  if(SysTick_Config(SystemCoreClock / 1000)) {
    while(1);
  }

  // Initialize the uart.
  uart_open(9600, USART_Mode_Rx | USART_Mode_Tx);

  // APPROACH 1: Echo character-by-character.
  while(1) {
    int ch = uart_getc();
    uart_putc(ch);
  }
}

// Timer code
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void SysTick_Handler (void){
  if (TimingDelay != 0x00)
    TimingDelay--;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  /* Infinite loop; use GDB to find out why we're here. */
  while (1);
}
#endif
