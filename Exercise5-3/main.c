#include <stm32f10x.h>
#include <stm32f10x_usart.h>
#include "uart.h"

void Delay(uint32_t nTime);

void buffer_char(int ch);
void flush_buffer();

#define LINE_BUFFER_LEN 100
static int buffer[LINE_BUFFER_LEN];
static int next_idx = 0;

main() {
  // Iniialize timer tick.
  if(SysTick_Config(SystemCoreClock / 1000)) {
    while(1);
  }

  // Initialize the uart.
  uart_open(9600, USART_Mode_Rx | USART_Mode_Tx);

  // APPROACH 1: Echo character-by-character.
  /*while(1) {
    int ch = uart_getc();
    uart_putc(ch);
  }*/

  // APPROACH 2: Echo line-by-line. I am using a fixed
  // width buffer here; ideally, it would be a dynamically
  // sized array, but that's too much for this particular
  // exercise, as the lack of interrupts are the main problem here.
  while(1) {
    int ch = uart_getc();
    buffer_char(ch);
    if (ch == '\r') {
      flush_buffer();
    }
  }
}

void buffer_char(int ch) {
  // If line is longer than LINE_BUFFER_LEN,
  // preemptively flush it to prevent buffer overflow.
  if (next_idx >= LINE_BUFFER_LEN) {
    flush_buffer();
  }
  buffer[next_idx++] = ch;
}

void flush_buffer() {
  int i;
  for (i = 0; i < next_idx; i++) {
    if (buffer[i] == '\r') {
      // Precede carraige returns with newlines
      // to ensure proper display in screen.
      uart_putc('\n');
    }
    uart_putc(buffer[i]);
  }
  next_idx = 0;
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
