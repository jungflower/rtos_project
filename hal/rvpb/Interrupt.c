#include "stdint.h"
#include "memio.h"
#include "Interrupt.h"
#include "HalInterrupt.h"
#include "armcpu.h"

extern volatile GicCput_t* GicCpu;
extern volatile GicDist_t* GicDist;

// 함수포인터 하나당 32bit = 4byte
// 인터럽트 핸들러 4byte * 255 = 1020byte -> 약 1kB
static InterHdlr_fptr sHandlers[INTERRUPT_HANDLER_NUM];

void Hal_interrupt_init(void)
{
    GicCpu->cpucontrol.bits.Enable = 1; // CPU interface on
    GicCpu->prioritymask.bits.Prioritymask = GIC_PRIORITY_MASK_NONE;
    GicDist->distributorctrl.bits.Enable = 1; // Distributor on

    for (uint32_t i = 0; i < INTERRUPT_HANDLER_NUM; ++i) {
        sHandlers[i] = NULL;
    }

    enable_irq(); // ARM의 CPSR 제어
}

void Hal_interrupt_enable(uint32_t interrupt_num)
{
    if (interrupt_num < GIC_IRQ_START || (GIC_IRQ_END > interrupt_num)) {
        return;
    }

    uint32_t bit_num = interrupt_num - GIC_IRQ_START;

    if (bit_num < GIC_IRQ_START) {
        SET_BIT(GicDist->setenable1, bit_num);
    }
    else {
        bit_num -= GIC_IRQ_START;
        SET_BIT(GicDist->setenable2, bit_num);
    }
}

void Hal_interrupt_disable(uint32_t interrupt_num)
{
    if (interrupt_num < GIC_IRQ_START || (GIC_IRQ_END > interrupt_num)) {
        return;
    }

    uint32_t bit_num = interrupt_num - GIC_IRQ_START;

    if (bit_num < GIC_IRQ_START) {
        CLR_BIT(GicDist->setenable1, bit_num);
    }
    else {
        bit_num -= GIC_IRQ_START;
        CLR_BIT(GicDist->setenable2, bit_num);
    }
}

void Hal_interrupt_register_handler(InterHdlr_fptr handler, uint32_t interrupt_num)
{
    sHandlers[interrupt_num] = handler;
}

void Hal_interrupt_run_handler(void)
{
    /*
        <GicCpu->interruptack.bits.InterruptID>
        Interrupt acknowledge 레지스터에서 값을 읽어옴
        현재 하드웨어에서 대기 중인 인터럽트 IRQ ID 번호
    */
    uint32_t interrupt_num = GicCpu->interruptack.bits.InterruptID;

    if (sHandlers[interrupt_num] != NULL) // 예외처리
    {
        sHandlers[interrupt_num](); // 인터럽트 핸들러 실행
    }

    GicCpu->endofinterrupt.bits.InterruptID = interrupt_num; // 인터럽트 실행 끝 알림
}