#include "stdint.h"
#include "HalUart.h"
#include "stdio.h"
#include "stdarg.h"

#define PRINTF_BUF_LEN  1024

static char sPrintf_buf[PRINTF_BUF_LEN];   // 1KB

uint32_t putstr(const char* s)
{
    uint32_t c = 0; // 글자 수
    while (*s) {
        Hal_uart_put_char(*s++);
        c++;
    }
    return c;
}

uint32_t debug_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vsprintf(sPrintf_buf, format, args);
    va_end(args);

    return putstr(sPrintf_buf);

}

uint32_t vsprintf(char* buf, const char* format, va_list arg)
{
    uint32_t c = 0;

    char        ch; // %c
    char* str; // %s
    uint32_t    uint; // %u
    uint32_t    hex; // %x

    for (uint32_t i = 0; format[i]; i++)
    {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
            case 'c':
                ch = (char)va_arg(arg, int32_t); // char도 실제론 int로 들어오기 때문에, int형으로 꺼내고 char형으로 cast
                buf[c++] = ch;
                break;
            case 's':
                str = (char*)va_arg(arg, char*);
                if (str == NULL) {
                    str = "(null)";
                }
                while (*str)
                {
                    buf[c++] = (*str++);
                }
                break;
            case 'u':
                uint = (uint32_t)va_arg(arg, uint32_t);
                c += utoa(&buf[c], uint, utoa_dec);
                break;
            case 'x':
                hex = (uint32_t)va_arg(arg, uint32_t);
                c += utoa(&buf[c], hex, utoa_hex);
                break;
            }
        }
        else {
            buf[c++] = format[i];
        }
    }

    if (c >= PRINTF_BUF_LEN) {
        buf[0] = '\0';
        return 0;
    }

    buf[c] = '\0';
    return c;
}

uint32_t utoa(char* buf, uint32_t val, utoa_t base)
{
    uint32_t c = 0;
    int32_t idx = 0;
    char tmp[11]; // it is big enough for store 32bit int

    do {
        uint32_t t = val % (uint32_t)base; // base = type(decimal or hex)
        // if (t >= 10) {
        //     t += 'A' - '0' - 10; // 10 ~ 15는 'A' ~ 'F'로 변환
        // }
        // tmp[idx] = (t + '0'); // 숫자를 문자로 변환하여 저장
        tmp[idx] = (t < 10) ? (t + '0') : (t - 10 + 'A');
        val /= base; // 다음 자릿수로 이동
        idx++;
    } while (val);

    // reverse
    idx--;
    while (idx >= 0) {
        buf[c++] = tmp[idx];
        idx--;
    }

    return c;
}
