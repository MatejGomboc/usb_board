#pragma once

#include <cstdint>

namespace Rtos {
    class Isrs {
    public:
        Isrs() = delete;
        static void svc(uint32_t svc_num, uint32_t* args);
        static void pendSv();
        static void sysTick();
    };
}
