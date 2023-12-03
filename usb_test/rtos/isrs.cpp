#include "isrs.hpp"
#include "threads.hpp"
#include "svc_numbers.hpp"
#include <cstdint>

namespace Rtos {

    void Isrs::svc(uint32_t svc_num, uint32_t* args)
    {
        switch (svc_num) {

        case static_cast<uint32_t>(SvcNumber::CREATE_THREAD): {
            void (*thread_handler)() = reinterpret_cast<void(*)()>(args[0]);
            uint32_t thread_stack_size = args[1];
            uint32_t* stack = args - 8;
            stack[0] = Threads::svcCreateThread(thread_handler, thread_stack_size); // R0
            break;
        }

        case static_cast<uint32_t>(SvcNumber::RESCHEDULE): {
            Threads::svcRunNextThread();
            break;
        }

        case static_cast<uint32_t>(SvcNumber::STOP_THREAD): {
            Threads::svcStopCurrentThread();
            break;
        }

        default: {
            while(true); // should never be reached
        }

        }
    }

    void Isrs::pendSv()
    {
        asm volatile("MOVS r0, %[svc_num]" : : [svc_num] "I" (SvcNumber::RESCHEDULE) : "r0");
        asm volatile("SVC %[svc_num]" : : [svc_num] "I" (SvcNumber::RESCHEDULE));
    }

    void Isrs::sysTick()
    {
        asm volatile("MOVS r0, %[svc_num]" : : [svc_num] "I" (SvcNumber::RESCHEDULE) : "r0");
        asm volatile("SVC %[svc_num]" : : [svc_num] "I" (SvcNumber::RESCHEDULE));
    }

}
