#pragma once

#include <cstdint>

namespace Rtos {
    enum class SvcNumber : uint8_t {
        RESCHEDULE = 0,
        CREATE_THREAD = 1,
        STOP_THREAD = 2
    };
}
