#include "stdint.h"
#include "HalUart.h"
#include "HalInterrupt.h"

#include "stdio.h"
static void HW_init(void);
static void Printf_test(void);

void main(void)
{
    HW_init();

    uint32_t i = 100;
    while (i--) {
        Hal_uart_put_char('N');
    }
    Hal_uart_put_char('\n');

    putstr("Hello world!\n");

    Printf_test();

    i = 50;
    while (i--) {
        uint8_t ch = Hal_uart_get_char();
        Hal_uart_put_char(ch);
    }
}

static void HW_init(void)
{
    Hal_interrupt_init();
    Hal_uart_init();
}

static void Printf_test()
{
    char* str = "printf pointer test";
    char* nullptr = 0;
    uint32_t i = 5;
    //uint32_t* sysctrl0 = (uint32_t*)0x10001000;

    debug_printf("%s\n", "Hello printf");
    debug_printf("output string pointer: %s\n", str);
    debug_printf("%s is null pointer, %u number\n", nullptr, 10);
    debug_printf("%u = 5\n", i);
    debug_printf("dec = %u hex = %x\n", 0xff, 0xff);
    debug_printf("print zero %u\n", 0);
    //debug_printf("SYSCTRL0 %x\n", *sysctrl0);
}