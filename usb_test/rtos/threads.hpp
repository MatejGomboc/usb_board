#pragma once

#include "isrs.hpp"
#include <cstdint>
#include <cstddef>

namespace Rtos {
    class Threads {
    public:
        Threads() = delete;
        static bool createThread(void (*handler)(), uint32_t stack_size);
        static void yieldThread();

    private:
        friend class Isrs;

        struct MainThread {
            enum class State : uint8_t {
                PAUSED = 0,
                RUNNING = 1
            };

            MainThread();

            State state{ State::RUNNING } ;
            uint32_t* stack_pointer;
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

        static void requestCurrentThreadStop();

        static bool svcCreateThread(void (*handler)(), uint32_t stack_size);
        static void svcRunNextThread();
        static void svcStopCurrentThread();

        static MainThread m_main_thread;
        static Thread m_threads[MAX_NUM_OF_THREADS];
        static size_t m_num_of_active_threads; // 1 means that only main thread is active
        static size_t m_current_thread_idx; // 0 means main thread
        static uint32_t* m_threads_stack_bottom;
    };
}
