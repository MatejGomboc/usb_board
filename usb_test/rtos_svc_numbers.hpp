#pragma once

#ifndef KERNEL_CODE
#error "This header file is part of RTOS kernel and should not be used directly in user code!"
#endif

#include <cstdint>

namespace Rtos::Kernel {
    enum class SvcNumber : uint8_t {
        RESCHEDULE = 0,
        CREATE_THREAD = 1,
        STOP_THREAD = 2
    };
}
