#include "rtos_api.hpp"
#define KERNEL_CODE
#include "rtos_svc_numbers.hpp"
#undef KERNEL_CODE
#include "cortexm0/scb.hpp"
#include <cstdint>

bool Rtos::Api::createThread(void (*handler)(), uint32_t stack_size)
{
    asm volatile("PUSH {%0, %1}" : : "r" (reinterpret_cast<uint32_t>(handler)), "r" (stack_size) : "memory");

    asm volatile("MOV r1, sp" : : : "r1");
    asm volatile("MOVS r0, %[svc_number]" : : [svc_number] "I" (Rtos::Kernel::SvcNumber::CREATE_THREAD) : "r0");

    asm volatile("SVC %[svc_number]" : : [svc_number] "I" (Rtos::Kernel::SvcNumber::CREATE_THREAD));

    bool status;
    asm volatile("MOV %[output], r0" : [output] "=r" (status));
    return status;
}

void Rtos::Api::yieldThread()
{
    CortexM0::Scb::Icsr icsr{ CortexM0::Scb::registers()->icsr };
    icsr.bits.pend_sv_set = true;
    CortexM0::Scb::registers()->icsr = icsr.value;
}
