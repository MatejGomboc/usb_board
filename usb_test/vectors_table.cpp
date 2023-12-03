#include "rtos/isrs.hpp"
#include <cstdint>

extern uint32_t __GLOBAL_STACK_TOP__;

extern "C" void resetIsr();
extern void nmiIsr();
extern void hardFaultIsr();
extern void unhandledIrqIsr();

__attribute__((section(".vectors_table"), used))
void (* const vectors_table[])() = {
    reinterpret_cast<void(*)()>(&__GLOBAL_STACK_TOP__),
    resetIsr,
    nmiIsr,
    hardFaultIsr,
    unhandledIrqIsr,
    unhandledIrqIsr,
    unhandledIrqIsr,
    unhandledIrqIsr,
    unhandledIrqIsr,
    unhandledIrqIsr,
    unhandledIrqIsr,
    reinterpret_cast<void(*)()>(Rtos::Isrs::svc),
    unhandledIrqIsr,
    unhandledIrqIsr,
    Rtos::Isrs::pendSv,
    Rtos::Isrs::sysTick,
    unhandledIrqIsr, // wwdgIrqIsr
    unhandledIrqIsr, // pvdVddio2IrqIsr
    unhandledIrqIsr, // rtcIrqIsr
    unhandledIrqIsr, // flashIrqIsr
    unhandledIrqIsr, // rccCrsIrqIsr
    unhandledIrqIsr, // exti_0_1_IrqIsr
    unhandledIrqIsr, // exti_2_3_IrqIsr
    unhandledIrqIsr, // exti_4_15_IrqIsr
    unhandledIrqIsr, // tscIrqIsr
    unhandledIrqIsr, // dma1Channel_1_IrqIsr
    unhandledIrqIsr, // dma1Channel_2_3_IrqIsr
    unhandledIrqIsr, // dma1Channel_4_5_6_7_IrqIsr
    unhandledIrqIsr, // adc1CompIrqIsr
    unhandledIrqIsr, // tim1BrkUpTrgComIrqIsr
    unhandledIrqIsr, // tim1CcIrqIsr
    unhandledIrqIsr, // tim2IrqIsr
    unhandledIrqIsr, // tim3IrqIsr
    unhandledIrqIsr, // tim6DacIrqIsr
    unhandledIrqIsr, // tim7IrqIsr
    unhandledIrqIsr, // tim14IrqIsr
    unhandledIrqIsr, // tim15IrqIsr
    unhandledIrqIsr, // tim16IrqIsr
    unhandledIrqIsr, // tim17IrqIsr
    unhandledIrqIsr, // i2c1IrqIsr
    unhandledIrqIsr, // i2c2IrqIsr
    unhandledIrqIsr, // spi1IrqIsr
    unhandledIrqIsr, // spi2IrqIsr
    unhandledIrqIsr, // usart_1_IrqIsr
    unhandledIrqIsr, // usart_2_IrqIsr
    unhandledIrqIsr, // usart_3_4_IrqIsr
    unhandledIrqIsr, // cecCanIrqIsr
    unhandledIrqIsr  // usbIrqIsr
};
