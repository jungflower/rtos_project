#ifndef HAL_HALUART_H_
#define HAL_HALUART_H_

void        Hal_uart_init(void); // 초기화
void        Hal_uart_put_char(uint8_t ch); // 한 글자 출력
uint8_t     Hal_uart_get_char(void); // 한 글자 입력

#endif /* HAL_HALUART_H_ */