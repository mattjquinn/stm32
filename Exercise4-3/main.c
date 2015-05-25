#include <stm32f10x.h>

/*
 * I defined these for use in testing while working on
 * this exercise. By reading the values from these
 * addresses at breakpoints, I was able to
 * see changes to the memory locations themselves at runtime.
 * To completely remove the dependency on <stm32f10x.h>, these
 * can be read to and written from directly.
 */
#define APB2ENR_REG *((volatile uint32_t*)0x40021018);
#define GPIOA_CRL_REG *((volatile uint32_t*)0x40010800);
#define GPIOC_CRH_REG *((volatile uint32_t*)0x40011004);

static volatile unsigned char push_btn_state;

typedef struct {
  unsigned char pin0 : 1;
  unsigned char pins1to7 : 7;
  unsigned char pin8 : 1;
  unsigned char pins9to15: 7;
} GPIODataRegister;

main() {

  // Enable peripheral clocks for GPIOA and GPIOC
  RCC->APB2ENR |= 0x14; // GPIOA (0x4) and GPIOC (0x10)

  // Configure push button on pin 0 for floating input.
  // High is pin 7; low is pin 0. Reset state for all
  // pins is 0x4 (CNFx = 0x01, MODEx = 0x00) for floating input,
  // so here we (superfluously) reaffirm that the
  // default is desired for pin 7.
  GPIOA->CRL = 0x44444444;

  // Configure blue LED on pin 8 for push-pull output at 2MHz
  // High is pin 15; low is pin 8. Reset state for all pins is
  // 0x4 as described above; here we want CNF8 = 0x00 and MODE8 =
  // 0x10 for push-pull output at 2MHz. Note that you cannot
  // OR the register with 0x2; doing so will result in an incorrect
  // value of 0x6 for CNF8:MODE8.
  GPIOC->CRH = 0x44444442;

  /*
   * Continually read the state of GPIOA pin0 (the push button) and
   * write that state out to GPIOC pin8 (the LED). Mapping a custom
   * struct to the data registers prevents the need for bit masks.
   */
  while(1) {
    push_btn_state = ((GPIODataRegister*)&GPIOA->IDR)->pin0;
    ((GPIODataRegister*)&GPIOC->ODR)->pin8 = push_btn_state;
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
  /* Infinite loop; use GDB to find out why we're here. */
  while (1);
}
#endif
