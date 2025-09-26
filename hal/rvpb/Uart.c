#include  "stdint.h"
#include "Uart.h"
#include  "HalUart.h"
#include "HalInterrupt.h"

extern volatile PL011_t* Uart;
static void interrupt_handler(void);

void Hal_uart_init(void)
{
    // Enable UART
    Uart->uartcr.bits.UARTEN = 0; // UART 하드웨어 off
    Uart->uartcr.bits.TXE = 1; // UART 출력 on (송신)
    Uart->uartcr.bits.RXE = 1; // UART 입력 on (수신)
    Uart->uartcr.bits.UARTEN = 1; // UART 하드웨어 on

    // Register UART Interrupt handler
    Hal_interrupt_enable(UART_INTERRUPT0);
    Hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0)
}

void Hal_uart_put_char(uint8_t ch)
{
    // TXFF(Transmit FIFO Full)
    while (Uart->uartfr.bits.TXFF); // 출력 버퍼가 빌때 까지 기다림
    Uart->uartdr.all = (ch & 0xFF); // 한글자 씩 출력버퍼로 출력(FIFO에 데이터 전송)
}

uint8_t Hal_uart_get_char(void)
{
    uint32_t data;

    while (Uart->uartfr.bits.RXFE);

    data = Uart->uartdr.all; // 레지스터 접근

    // Check for an error flag
    if (data & 0xFFFFFF00) // FE, PE, BE, OE (error flag -> 1이면 error)
    {
        // Clear the error
        Uart->uartrsr.all = 0xFF; // 레지스터 접근
        return 0;
    }

    return (uint8_t)(data & 0xFF);
}

static void interrupt_handler(void)
{
    uint8_t ch = Hal_uart_get_char();
    Hal_uart_put_char(ch);
}