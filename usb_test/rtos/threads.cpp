#include "threads.hpp"
#include "svc_numbers.hpp"
#include "cortexm0/special_regs.hpp"
#include "cortexm0/scb.hpp"
#include <cstdint>
#include <cstddef>

extern uint32_t __PROCESS_STACK_BOTTOM__;
extern uint32_t __PROCESS_STACK_TOP__;

extern uint32_t __MAIN_STACK_BOTTOM__;
extern uint32_t __MAIN_STACK_TOP__;

namespace Rtos {

    Threads::MainThread Threads::m_main_thread;
    Threads::Thread Threads::m_threads[MAX_NUM_OF_THREADS];
    size_t Threads::m_num_of_active_threads(1); // 1 means that only main thread is active
    size_t Threads::m_current_thread_idx(0); // 0 means main thread
    uint32_t* Threads::m_threads_stack_bottom(&__PROCESS_STACK_TOP__ - MAIN_THREAD_STACK_SIZE);

    Threads::MainThread::MainThread() :
        stack_pointer(&__PROCESS_STACK_TOP__)
    {
    }

    bool Threads::createThread(void (*handler)(), uint32_t stack_size)
    {
        asm volatile("PUSH {%0, %1}" : : "r" (reinterpret_cast<uint32_t>(handler)), "r" (stack_size) : "memory");

        asm volatile("MOV r1, sp" : : : "r1");
        asm volatile("MOVS r0, %[svc_number]" : : [svc_number] "I" (SvcNumber::CREATE_THREAD) : "r0");

        asm volatile("SVC %[svc_number]" : : [svc_number] "I" (SvcNumber::CREATE_THREAD));

        bool status;
        asm volatile("MOV %[output], r0" : [output] "=r" (status));
        return status;
    }

    void Threads::yieldThread()
    {
        CortexM0::Scb::Icsr icsr{ CortexM0::Scb::registers()->icsr };
        icsr.bits.pend_sv_set = true;
        CortexM0::Scb::registers()->icsr = icsr.value;
    }

    void Threads::requestCurrentThreadStop()
    {
        asm volatile("MOVS r0, %[svc_num]" : : [svc_num] "I" (SvcNumber::STOP_THREAD) : "r0");
        asm volatile("SVC %[svc_num]" : : [svc_num] "I" (SvcNumber::STOP_THREAD));
    }

    bool Threads::svcCreateThread(void (*new_thread_handler)(), uint32_t new_thread_stack_size)
    {
        // check if too many threads
        if (m_num_of_active_threads >= MAX_NUM_OF_THREADS) {
            return false;
        }

        // check if not enough process stack space left
        if (m_threads_stack_bottom < &__PROCESS_STACK_BOTTOM__ + new_thread_stack_size) {
            return false;
        }

        // increase num of active threads
        m_num_of_active_threads++;

        // setup new thread and put it into PAUSED state
        uint32_t* new_thread_stack_pointer = m_threads_stack_bottom - 8;
        m_threads[m_num_of_active_threads].state = Thread::State::PAUSED;
        m_threads[m_num_of_active_threads].stack_top = m_threads_stack_bottom;
        m_threads[m_num_of_active_threads].stack_pointer = new_thread_stack_pointer;
        m_threads[m_num_of_active_threads].stack_size = new_thread_stack_size;
        m_threads[m_num_of_active_threads].handler = new_thread_handler;

        // calculate new threads stack bottom
        m_threads_stack_bottom -= new_thread_stack_size;

        // simulate stack frame for the new thread
        CortexM0::Psr psr;
        psr.bits.thumb_mode = true;
        new_thread_stack_pointer[7] = psr.value; // PSR
        new_thread_stack_pointer[6] = reinterpret_cast<uint32_t>(new_thread_handler); // PC
        new_thread_stack_pointer[5] = reinterpret_cast<uint32_t>(requestCurrentThreadStop) | 1; // LR
        new_thread_stack_pointer[4] = 0; // R12
        new_thread_stack_pointer[3] = 0; // R3
        new_thread_stack_pointer[2] = 0; // R2
        new_thread_stack_pointer[1] = 0; // R1
        new_thread_stack_pointer[0] = 0; // R0

        return true;
    }

    void Threads::svcRunNextThread()
    {
        // nothing to do if only single thread is running
        if (m_num_of_active_threads == 1) {
            return;
        }

        // pause the current thread
        if (m_current_thread_idx == 0) {
            m_main_thread.state = MainThread::State::PAUSED;
            m_main_thread.stack_pointer = reinterpret_cast<uint32_t*>(CortexM0::getPspReg());
        } else {
            m_threads[m_current_thread_idx - 1].state = Thread::State::PAUSED;
            m_threads[m_current_thread_idx - 1].stack_pointer = reinterpret_cast<uint32_t*>(CortexM0::getPspReg());
        }

        // run the next thread
        m_current_thread_idx++;
        if (m_current_thread_idx >= m_num_of_active_threads) {
            m_current_thread_idx = 0;
        }

        if (m_current_thread_idx == 0) {
            m_main_thread.state = MainThread::State::RUNNING;
            CortexM0::setPspReg(reinterpret_cast<uint32_t>(m_main_thread.stack_pointer));
        } else {
            m_threads[m_current_thread_idx - 1].state = Thread::State::RUNNING;
            CortexM0::setPspReg(reinterpret_cast<uint32_t>(m_threads[m_current_thread_idx - 1].stack_pointer));
        }
    }

    void Threads::svcStopCurrentThread()
    {
        if ((m_current_thread_idx == 0) || (m_num_of_active_threads <= 1)) {
            while (true); // should never be reached
        }

        if (m_current_thread_idx < m_num_of_active_threads - 1) {
            // remove gap in stack
            uint32_t size = m_threads[m_current_thread_idx - 1].stack_top - m_threads[m_num_of_active_threads - 2].stack_size
                - m_threads_stack_bottom;

            uint32_t* dest_addr = m_threads[m_current_thread_idx - 1].stack_top - 1;
            uint32_t* src_addr = m_threads[m_current_thread_idx].stack_top - 1;

            while (size--) {
                *(dest_addr--) = *(src_addr--);
            }
        }

        m_threads_stack_bottom += m_threads[m_current_thread_idx - 1].stack_size;

        // remove gap in threads
        for (size_t thread_idx = m_current_thread_idx; thread_idx < m_num_of_active_threads - 1; thread_idx++) {
            m_threads[thread_idx - 1].state = m_threads[thread_idx].state;
            m_threads[thread_idx - 1].stack_top = m_threads[thread_idx].stack_top;
            m_threads[thread_idx - 1].stack_pointer = m_threads[thread_idx].stack_pointer;
            m_threads[thread_idx - 1].stack_size = m_threads[thread_idx].stack_size;
            m_threads[thread_idx - 1].handler = m_threads[thread_idx].handler;
        }

        // invalidate the last thread
        m_threads[m_num_of_active_threads - 2].state = Thread::State::STOPPED;

        m_num_of_active_threads--;

        if (m_current_thread_idx >= m_num_of_active_threads) {
            m_current_thread_idx = 0;
        }

        // run the next thread
        if (m_current_thread_idx == 0) {
            m_main_thread.state = MainThread::State::RUNNING;
            CortexM0::setPspReg(reinterpret_cast<uint32_t>(m_main_thread.stack_pointer));
        } else {
            m_threads[m_current_thread_idx - 1].state = Thread::State::RUNNING;
            CortexM0::setPspReg(reinterpret_cast<uint32_t>(m_threads[m_current_thread_idx - 1].stack_pointer));
        }
    }

}
