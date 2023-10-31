#include "linker_symbols.hpp"
#include "cortexm0/special_regs.hpp"
#define KERNEL_CODE
#include "rtos_svc_numbers.hpp"
#undef KERNEL_CODE
#include <cstdint>
#include <cstddef>

namespace Rtos::Kernel {

    struct MainThread {
        enum class State : uint8_t {
            PAUSED = 0,
            RUNNING = 1
        };

        State state{ State::RUNNING } ;
        uint32_t* stack_pointer{ __PROCESS_STACK_TOP__ };
        uint32_t stack_size{ MAIN_THREAD_STACK_SIZE };
    };

    struct Thread {
        enum class State : uint8_t {
            PAUSED = 0,
            RUNNING = 1,
            STOPPED = 2
        };

        State state{ State::STOPPED };
        uint32_t* stack_top{ nullptr };
        uint32_t* stack_pointer{ nullptr };
        uint32_t stack_size{ 0 };
        void (*handler)(){ nullptr };
    };

    static MainThread m_main_thread;
    static Thread m_threads[MAX_NUM_OF_THREADS];
    static size_t m_num_of_active_threads{ 1 }; // 1 means that only main thread is active
    static size_t m_current_thread_idx{ 0 }; // 0 means main thread
    static uint32_t* m_threads_stack_bottom{ __PROCESS_STACK_TOP__ - MAIN_THREAD_STACK_SIZE };

    static void requestCurrentThreadStop()
    {
        asm volatile("MOVS r0, %[svc_num]" : : [svc_num] "I" (Rtos::Kernel::SvcNumber::STOP_THREAD) : "r0");
        asm volatile("SVC %[svc_num]" : : [svc_num] "I" (Rtos::Kernel::SvcNumber::STOP_THREAD));
    }

    bool createThread(void (*new_thread_handler)(), uint32_t new_thread_stack_size)
    {
        // check if too many threads
        if (m_num_of_active_threads >= MAX_NUM_OF_THREADS) {
            return false;
        }

        // check if not enough process stack space left
        if (m_threads_stack_bottom < __PROCESS_STACK_BOTTOM__ + new_thread_stack_size) {
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

    void runNextThread()
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

    void stopCurrentThread()
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