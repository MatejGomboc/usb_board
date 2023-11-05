#pragma once

#ifndef KERNEL_CODE
#error "This header file is part of RTOS kernel and should not be used directly in user code!"
#endif

#include <cstdint>

namespace Rtos::Kernel {
    void initKernel();
    bool createThread(void (*handler)(), uint32_t stack_size);
    void runNextThread();
    void stopCurrentThread();
}
