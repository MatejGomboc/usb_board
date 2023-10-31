#pragma once

#include <cstdint>

namespace Rtos::Api {
    bool createThread(void (*handler)(), uint32_t stack_size);
    void yieldThread();
}
