#ifndef INCLUDE_STDARG_H_
#define INCLUDE_STDARG_H_

typedef __builtin_va_list va_list;

#define va_start(v,l)   __builtin_va_start(v,l) // 가변 인자 처리를 시작
#define va_end(v)       __builtin_va_end(v) // 가변 인자 처리 종료
#define va_arg(v,l)     __builtin_va_arg(v,l) // 가변 인자 중 다음 값을 가져옴 (형 지정 필요)

#endif /* INCLUDE_STDARG_H_ */