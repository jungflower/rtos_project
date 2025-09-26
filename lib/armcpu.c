#include "armcpu.h"

void enable_irq(void)
{
    __asm__("PUSH {r0, r1}"); // r0, r1 레지스트 보존
    __asm__("MRS  r0, cpsr"); // 현재 cpsr값 r0로 읽음 (move from sepcial register)
    __asm__("BIC  r1, r0, #0x80"); // CPSR의 IRQ 마스크 비트 위치인 7번 비트에 1로 설정
    __asm__("MSR  cpsr, r1"); // 바뀐 r1값을 cpsr에 반영 -> 즉시 IRQ 허용상태로 전환 (move to special register)
    __asm__("POP {r0, r1}");
}

void enable_fiq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS  r0, cpsr");
    __asm__("BIC  r1, r0, #0x40"); // // CPSR의 FIQ 마스크 비트 위치인 6번 비트에 1로 설정
    __asm__("MSR  cpsr, r1");
    __asm__("POP {r0, r1}");
}

void disable_irq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS  r0, cpsr");
    __asm__("ORR  r1, r0, #0x80");
    __asm__("MSR  cpsr, r1");
    __asm__("POP {r0, r1}");
}

void disable_fiq(void)
{
    __asm__("PUSH {r0, r1}");
    __asm__("MRS  r0, cpsr");
    __asm__("ORR  r1, r0, #0x40");
    __asm__("MSR  cpsr, r1");
    __asm__("POP {r0, r1}");
}
