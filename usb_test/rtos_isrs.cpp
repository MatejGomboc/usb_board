#include "cortexm0/special_regs.hpp"
#include "cortexm0/exceptions.hpp"
#define KERNEL_CODE
#include "rtos_kernel.hpp"
#include "rtos_svc_numbers.hpp"
#undef KERNEL_CODE
#include <cstdint>

extern "C" void svcIsr(uint32_t svc_num, uint32_t* stack)
{
    switch (svc_num) {

    case static_cast<uint32_t>(Rtos::Kernel::SvcNumber::CREATE_THREAD): {
        void (*thread_handler)() = reinterpret_cast<void(*)()>(stack[9]);
        uint32_t thread_stack_size = stack[8];
        stack[0] = Rtos::Kernel::createThread(thread_handler, thread_stack_size); // R0
        break;
    }

    case static_cast<uint32_t>(Rtos::Kernel::SvcNumber::RESCHEDULE): {
        Rtos::Kernel::runNextThread();
        break;
    }

    case static_cast<uint32_t>(Rtos::Kernel::SvcNumber::STOP_THREAD): {
        Rtos::Kernel::stopCurrentThread();
        break;
    }

    default: {
        while(true); // should never be reached
    }

    }
}

extern "C" void pendSvIsr()
{
    asm volatile("MOVS r0, %[svc_num]" : : [svc_num] "I" (Rtos::Kernel::SvcNumber::RESCHEDULE) : "r0");
    asm volatile("SVC %[svc_num]" : : [svc_num] "I" (Rtos::Kernel::SvcNumber::RESCHEDULE));
}

extern "C" void sysTickIsr()
{
    asm volatile("MOVS r0, %[svc_num]" : : [svc_num] "I" (Rtos::Kernel::SvcNumber::RESCHEDULE) : "r0");
    asm volatile("SVC %[svc_num]" : : [svc_num] "I" (Rtos::Kernel::SvcNumber::RESCHEDULE));
}
