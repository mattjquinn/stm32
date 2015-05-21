Page 60 prompts:

"Modify your program to cause an assertion violation – for example re-
placing GPIOC with 66 when initializing the pin – and use GDB to find the
place in the library source code where an assertion failed."

So, at line 19, change first arg to GPIO_Init from GPIOC to 66 to cause assertion failure, then run:

$ arm-none-eabi-gdb Excerise4-1.elf
(gdb) target remote :4242
(gdb) load
(gdb) break assert_failed
(gdb) continue
... wait for breakpoint to be hit; output will be:

Note: automatically using hardware breakpoints for read-only addresses.

Breakpoint 1, assert_failed (
    file=0x8002b60 "/opt/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c", line=178) at main.c:53
53	  while (1);

(gdb) bt
... gdb will show backtrace as (pointing to line we changed before running gdb):

#0  assert_failed (
    file=0x8002b60 "/opt/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c", line=178) at main.c:53
#1  0x08000a7e in GPIO_Init (GPIOx=0x42, GPIO_InitStruct=0x20001fe4)
    at /opt/STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c:178
#2  0x0800079a in main () at main.c:19


NOTE: The first time I attempted this, when trying to execute bt, gdb would quit and show ***Stack smashing detected***. After I left it for a day and came back, involving a disconnect and reconnect of the STM32 to my Ubuntu VM, I no longer had this issue.

ALSO NOTE: You must add the following line to stm32f10x_conf.h in order to ensure that assertions are made in the libraries themselves:

#define USE_FULL_ASSERT 1
