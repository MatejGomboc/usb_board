#pragma once

#ifndef KERNEL_CODE
#error "This header file is part of RTOS kernel and should not be used directly in user code!"
#endif

#undef KERNEL_CODE

#include "linker_symbols.hpp"
#include "cortexm0/special_regs.hpp"
#include "cortexm0/scb.hpp"
#include "cortexm0/systick.hpp"
#include "cortexm0/exceptions.hpp"

#define KERNEL_CODE

#include <cstdint>

namespace Rtos::Kernel {
    static inline void initKernel()
    {
        // disable exceptions
        CortexM0::enableExceptions();

        // adjust SVCall priority
        CortexM0::Scb::Shpr2 shpr2 { CortexM0::Scb::registers()->shpr2 };
        shpr2.bits.sv_call_except_priority = 0x00;
        CortexM0::Scb::registers()->shpr2 = shpr2.value;

        // adjust SysTick and PendSV priorities
        CortexM0::Scb::Shpr3 shpr3 { CortexM0::Scb::registers()->shpr3 };
        shpr3.bits.pend_sv_except_priority = 0xFF;
        shpr3.bits.sys_tick_except_priority = 0xFE;
        CortexM0::Scb::registers()->shpr3 = shpr3.value;

        // configure SysTick timer but don't enable it yet
        CortexM0::SysTick::registers()->reload_val = SYSTICK_PERIOD_CYCLES;
        CortexM0::SysTick::registers()->current_val = 0;

        CortexM0::SysTick::CtrlStatus ctrl_status{ CortexM0::SysTick::registers()->ctrl_status };
        ctrl_status.bits.clk_source = static_cast<bool>(CortexM0::SysTick::CtrlStatus::ClkSource::CPU);
        ctrl_status.bits.exception_enabled = true;
        ctrl_status.bits.timer_enabled = false;
        CortexM0::SysTick::registers()->ctrl_status = ctrl_status.value;

        // set PSP to the process stack top
        CortexM0::setPspReg(reinterpret_cast<uint32_t>(__PROCESS_STACK_TOP__));

        // start using PSP
        CortexM0::Control control { CortexM0::getControlReg() };
        control.bits.active_stack_pointer = static_cast<bool>(CortexM0::Control::StackPointer::PSP);
        CortexM0::setControlReg(control);

        // set MSP to the main stack top
        CortexM0::setMspReg(reinterpret_cast<uint32_t>(__MAIN_STACK_TOP__));

        // enable exceptions
        CortexM0::enableExceptions();

        // branch to main()
        main();
    }

    bool createThread(void (*handler)(), uint32_t stack_size);
    void runNextThread();
    void stopCurrentThread();
}
